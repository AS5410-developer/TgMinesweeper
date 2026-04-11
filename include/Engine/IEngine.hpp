#ifndef INC_ENGINE_IENGINE_HPP
#define INC_ENGINE_IENGINE_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <Base/Types.hpp>
#include <BotAPI/IBotAPI.hpp>
#include <Engine/IConsole.hpp>
#include <FileSystem/IFileSystem.hpp>
#include <Launcher/ILauncher.hpp>
#include <Platform/IPlatform.hpp>
#include <Server/IServer.hpp>
#include <string>

namespace AS::Engine {
class ILauncher;

struct ModuleInfo {
  ModuleID ID;
  LibraryHandle Handle;
  std::string* Name;
  IModule* Module;
  bool Activated;
  bool LoadedByEngine;
};

class ENGINE_EXPORT IEngine : public IModule {
 public:
  virtual void Quit() = 0;
  virtual void QuitOnError(const IError& error) = 0;

  virtual ModuleID AddModule(IModule* module) = 0;
  virtual std::vector<ModuleInfo> GetModules() const = 0;
  virtual void RemoveModule(ModuleID module) = 0;

  virtual ResultOrError<ModuleID> LoadModule(const std::string& name) = 0;
  virtual ResultOrError<ModuleID> FindModuleByName(
      const std::string& name) const = 0;
  virtual const ModuleInfo* GetModuleInfo(ModuleID module) const = 0;
  virtual void DeactivateModule(ModuleID module) = 0;
  virtual void ActivateModule(ModuleID module) = 0;
  virtual void UnloadModule(ModuleID module) = 0;

  virtual void SetLauncherClass(ILauncher* launcher) = 0;

  virtual IConsole& GetConsole() = 0;
  virtual IPlatform& GetPlatform() = 0;
  virtual IFileSystem& GetFileSystem() = 0;
  virtual IServer* GetServer() = 0;
  virtual IBotAPI* GetBotAPI() = 0;

  virtual WindowSize GetWindowSize() const = 0;
  virtual IWindow* GetMainWindow() const = 0;

  virtual Tick GetCurrentTime() const = 0;
  virtual Tick GetTickrate() const = 0;
  virtual float GetDeltaTime() const = 0;

  virtual bool IsServer() const = 0;
  virtual bool IsSingleplayer() const = 0;

  virtual void SetIsSingleplayer(bool newFlag) = 0;

  virtual int GetStartArgc() = 0;
  virtual char** GetStartArgv() = 0;

  virtual ~IEngine() = default;
};
}  // namespace AS::Engine

#endif