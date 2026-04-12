#include <Modules/Engine.hpp>
#include <chrono>
#include <iostream>
#include <thread>
using namespace AS::Engine;

Engine::Engine() {}

std::chrono::steady_clock::time_point Engine::PrepareTick() {
  return std::chrono::high_resolution_clock::now();
}
std::chrono::steady_clock::time_point Engine::EndTick() {
  return std::chrono::high_resolution_clock::now();
}

void Engine::OnLoaded() {
  auto result = LoadModule("./bin/libPlatformSDL3.so");
  if (result.Failed()) {
    QuitOnError(result);
    return;
  }
  PlatformInstance =
      dynamic_cast<IPlatform*>(GetModuleInfo(result.GetResult())->Module);

  ConsoleInstance = Console(this);

  LoadModule("./bin/libCtrlUI.so");

  result = LoadModule("./bin/libFileSystem.so");
  if (result.Failed()) {
    QuitOnError(result);
    return;
  }
  FilesystemInstance =
      dynamic_cast<IFileSystem*>(GetModuleInfo(result.GetResult())->Module);

  FilesystemInstance->SetupGamePath("minesweeper2D");

  if (!IsServer()) {
    auto wind = PlatformInstance->CreateWindow();
    if (wind.Failed()) {
      QuitOnError(wind);
      return;
    }
    MainWindow = wind.GetResult();
    MainWindow->SetSize({800, 800});
    MainWindow->SetTitle("AS 2D Engine");
    MainWindow->SetSurfaceType(AS_ENGINE_IWINDOW_SURFACETYPE_VULKAN);
    MainWindow->Initialize();
    MainWindow->SetFullscreen(false);
  }

  result = LoadModule(FilesystemInstance->GetPath(
      "libTgBotAPI.so", AS_ENGINE_FILE_SYSTEM_BINDIR));
  if (result.Failed()) {
    QuitOnError(result);
    return;
  }
  BotAPIInstance =
      dynamic_cast<IBotAPI*>(GetModuleInfo(result.GetResult())->Module);

  result = LoadModule(FilesystemInstance->GetPath(
      "bin/libServer.so", AS_ENGINE_FILE_SYSTEM_GAMEDIR));
  if (result.Failed()) {
    QuitOnError(result);
    return;
  }
  ServerInstance =
      dynamic_cast<IServer*>(GetModuleInfo(result.GetResult())->Module);

  TicksThread = std::thread(&Engine::OnTick, this);
  ConsoleInstance << "Current engine's address in process virtual memory: "
                  << this << EndLine;
}
void Engine::OnRegisterOptions() {}
void Engine::OnUpdate() {
  if (MainWindow) MainWindow->Update();
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point endTime;
  std::vector<std::thread> threads;
  startTime = PrepareTick();
  for (uint64_t i = 0; i < Modules.size(); ++i) {
    if (!Modules.contains(i)) continue;
    if (Modules[i].Activated) {
      auto mod = Modules[i].Module;
      threads.emplace_back([mod]() { mod->OnUpdate(); });
    }
  }
  for (auto& thread : threads) {
    thread.join();
  }
  threads.clear();
  endTime = EndTick();
  DeltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(
                  endTime - startTime)
                  .count() /
              100000.0f;
}
void Engine::OnTick() {
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point endTime;
  int64_t end;
  std::chrono::steady_clock::time_point maxEndTime;
  while (GetTickrate() != -1) {
    startTime = PrepareTick();

    for (uint64_t i = 0; i < Modules.size(); ++i) {
      if (!Modules.contains(i)) continue;
      if (Modules[i].Activated) Modules[i].Module->OnTick();
    }
    ++CurrentTime;

    endTime = EndTick();

    end = std::chrono::duration_cast<std::chrono::milliseconds>(
              endTime.time_since_epoch())
              .count();
    maxEndTime = startTime + std::chrono::milliseconds(
                                 (int64_t)((1 / (double)TickInSecond) * 1000));
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            maxEndTime.time_since_epoch())
            .count() > end) {
      std::this_thread::sleep_until(maxEndTime);
    }
  }
}
void Engine::OnEnabled() {}
void Engine::OnDisabled() {
  TickInSecond = -1;
  if (TicksThread.joinable()) TicksThread.join();
  ConsoleInstance.Clean();
  for (const auto& [id, info] : Modules) {
    if (info.Activated) {
      info.Module->OnDisabled();
    }
  }
  std::vector<ModuleID> ids;
  for (const auto& [id, info] : Modules) {
    ids.push_back(id);
  }

  for (auto id : ids) {
    if (Modules[id].LoadedByEngine) {
      UnloadModule(id);
    } else {
      RemoveModule(id);
    }
  }
}

void Engine::Quit() {
  if (MainWindow)
    if (MainWindow->IsCreated()) MainWindow->Destroy();
  TickInSecond = -1;
}
void Engine::QuitOnError(const IError& error) {
  if (MainWindow)
    if (MainWindow->IsCreated()) MainWindow->Destroy();
  std::cerr << "FATAL ENGINE ERROR CALLED: " << error.What() << std::endl;
  Quit();
}

ModuleID Engine::AddModule(IModule* module) {
  std::string* name = new std::string(std::to_string(Modules.size()));

  ModuleInfo info = {.ID = Modules.size(), .Name = name};
  info.Module = module;
  info.LoadedByEngine = false;
  info.Activated = true;
  info.Handle = nullptr;

  Modules[info.ID] = std::move(info);
  module->OnLoaded();

  return info.ID;
}
std::vector<ModuleInfo> Engine::GetModules() const {
  std::vector<ModuleInfo> moduleInfos;
  for (const auto& [id, info] : Modules) {
    moduleInfos.push_back(info);
  }
  return moduleInfos;
}
void Engine::RemoveModule(ModuleID module) {
  if (!Modules.contains(module)) return;
  DeactivateModule(module);
  delete Modules[module].Name;
  delete Modules[module].Module;
  Modules.erase(module);
}

ResultOrError<ModuleID> Engine::LoadModule(const std::string& name) {
  std::string path = name;
  ModuleInfo info = {.ID = Modules.size(), .Name = new std::string(name)};

  auto Lib = LauncherInstance->SysLoadLibrary(path);
  if (Lib.Failed()) {
    return ResultOrError<ModuleID>(0, Lib.What(), true);
  }

  auto Proc = LauncherInstance->SysGetModuleFunc(Lib.GetResult());
  if (Proc.Failed()) {
    return ResultOrError<ModuleID>(0, Lib.What(), true);
  }

  info.Module = Proc.GetResult()(this);
  if (!info.Module)
    return ResultOrError<ModuleID>(0, "Module pointer = 0", true);
  info.LoadedByEngine = true;
  info.Activated = true;
  info.Handle = Lib.GetResult();

  Modules[info.ID] = info;
  info.Module->OnLoaded();

  return info.ID;
}
ResultOrError<ModuleID> Engine::FindModuleByName(
    const std::string& name) const {
  ModuleID moduleID = 0;
  auto ID = std::find_if(
      Modules.begin(), Modules.end(),
      [&name](
          const std::pair<const AS::Engine::ModuleID, AS::Engine::ModuleInfo>&
              entry) { return *entry.second.Name == name; });

  if (ID == Modules.end())
    return ResultOrError<ModuleID>(0, "Module not found", true);
  return ID->first;
}
const ModuleInfo* Engine::GetModuleInfo(ModuleID module) const {
  return &Modules.at(module);
}
void Engine::DeactivateModule(ModuleID module) {
  if (!Modules.contains(module)) return;
  if (!Modules[module].Activated) return;
  Modules[module].Module->OnDisabled();
  Modules[module].Activated = false;
}
void Engine::ActivateModule(ModuleID module) {
  if (!Modules.contains(module)) return;
  if (Modules[module].Activated) return;
  Modules[module].Activated = true;
  Modules[module].Module->OnEnabled();
}
void Engine::UnloadModule(ModuleID module) {
  DeactivateModule(module);
  delete Modules[module].Name;
  delete Modules[module].Module;
  if (!Modules[module].LoadedByEngine) {
    Modules.erase(module);
    return;
  }
  LauncherInstance->SysUnloadLibrary(Modules[module].Handle);
  Modules.erase(module);
}