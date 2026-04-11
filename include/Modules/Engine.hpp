#ifndef INC_ENGINE_HPP
#define INC_ENGINE_HPP

#include <engine_export.h>

#include <Engine/IEngine.hpp>
#include <Modules/Console.hpp>
#include <chrono>
#include <map>

namespace AS::Engine {

class ENGINE_EXPORT Engine final : public IEngine {
 public:
  Engine();

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  virtual void Quit() override;
  virtual void QuitOnError(const IError& error) override;

  virtual ModuleID AddModule(IModule* module) override;
  virtual std::vector<ModuleInfo> GetModules() const override;
  virtual void RemoveModule(ModuleID module) override;

  virtual ResultOrError<ModuleID> LoadModule(const std::string& name) override;
  virtual ResultOrError<ModuleID> FindModuleByName(
      const std::string& name) const override;
  virtual const ModuleInfo* GetModuleInfo(ModuleID module) const override;
  virtual void DeactivateModule(ModuleID module) override;
  virtual void ActivateModule(ModuleID module) override;
  virtual void UnloadModule(ModuleID module) override;

  virtual void SetLauncherClass(ILauncher* launcher) override {
    LauncherInstance = launcher;
  }

  virtual IConsole& GetConsole() override { return ConsoleInstance; }
  virtual IPlatform& GetPlatform() override { return *PlatformInstance; }
  virtual IFileSystem& GetFileSystem() override { return *FilesystemInstance; }
  virtual IServer* GetServer() override { return ServerInstance; };
  virtual IBotAPI* GetBotAPI() override { return BotAPIInstance; }

  virtual WindowSize GetWindowSize() const override {
    return MainWindow->GetSize();
  }

  virtual Tick GetCurrentTime() const override { return CurrentTime; }
  virtual Tick GetTickrate() const override { return TickInSecond; }
  virtual float GetDeltaTime() const override { return DeltaTime; }

  virtual bool IsServer() const override { return true; }
  virtual bool IsSingleplayer() const override { return Singleplayer; }

  virtual IWindow* GetMainWindow() const override { return MainWindow; }

  virtual void SetIsSingleplayer(bool newFlag) override {
    Singleplayer = newFlag;
  }

  virtual int GetStartArgc() override {
    return LauncherInstance->GetStartArgc();
  }
  virtual char** GetStartArgv() override {
    return LauncherInstance->GetStartArgv();
  }

  virtual ~Engine() = default;

 private:
  std::chrono::steady_clock::time_point PrepareTick();
  std::chrono::steady_clock::time_point EndTick();

  std::map<ModuleID, ModuleInfo> Modules;
  Tick CurrentTime;
  Tick TickInSecond = 128;
  bool Singleplayer;
  float DeltaTime;
  IPlatform* PlatformInstance;
  IFileSystem* FilesystemInstance;
  IWindow* MainWindow = 0;
  IBotAPI* BotAPIInstance;
  IServer* ServerInstance;
  Console ConsoleInstance;
  ILauncher* LauncherInstance;
};
}  // namespace AS::Engine

#endif