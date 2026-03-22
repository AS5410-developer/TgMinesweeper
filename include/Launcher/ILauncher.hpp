#ifndef INC_LAUNCHER_ILAUNCHER_HPP
#define INC_LAUNCHER_ILAUNCHER_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <Base/Types.hpp>
#include <Engine/IConsole.hpp>
#include <Engine/IEngine.hpp>
#include <string>

namespace AS::Engine {
class IEngine;
typedef IModule* (*GetModuleAPIFunc)(IEngine*);
typedef void (*LaunchFunc)(int argc, char** argv);

class ENGINE_EXPORT ILauncher : public IModule {
 public:
  virtual ResultOrError<LibraryHandle> SysLoadLibrary(
      const std::string& path) = 0;
  virtual ResultOrError<void*> SysGetFunc(LibraryHandle handle,
                                          const std::string& funcName) = 0;
  virtual void SysUnloadLibrary(LibraryHandle handle) = 0;

  virtual ResultOrError<GetModuleAPIFunc> SysGetModuleFunc(
      LibraryHandle handle) = 0;
  virtual ResultOrError<GetModuleAPIFunc> SysLoadModule(
      const std::string& path) = 0;

  virtual int GetStartArgc() = 0;
  virtual char** GetStartArgv() = 0;

  virtual ~ILauncher() = default;
};
}  // namespace AS::Engine

#endif