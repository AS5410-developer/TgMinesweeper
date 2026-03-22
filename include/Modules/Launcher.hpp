#ifndef INC_LAUNCHER_HPP
#define INC_LAUNCHER_HPP

#include <engine_export.h>

#include <Launcher/ILauncher.hpp>
#include <Modules/Engine.hpp>
#include <string>

namespace AS::Engine {

class Launcher final : public ILauncher {
 public:
  Launcher(int argc, char** argv);

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  virtual ResultOrError<LibraryHandle> SysLoadLibrary(
      const std::string& path) override;
  virtual ResultOrError<void*> SysGetFunc(LibraryHandle handle,
                                          const std::string& funcName) override;
  virtual void SysUnloadLibrary(LibraryHandle handle) override;

  virtual ResultOrError<GetModuleAPIFunc> SysGetModuleFunc(
      LibraryHandle handle) override;
  virtual ResultOrError<GetModuleAPIFunc> SysLoadModule(
      const std::string& path) override;

  void LaunchFailed(const char* reason, ...);
  bool IsFailed() { return Failed; }

  virtual int GetStartArgc() override { return argc; }
  virtual char** GetStartArgv() override { return argv; }

  virtual ~Launcher() = default;

 private:
  IEngine* EnginePtr;
  bool Failed = false;
  int argc;
  char** argv;
};
}  // namespace AS::Engine

#endif