#ifndef INC_FILESYSTEM_IFILESYSTEM_HPP
#define INC_FILESYSTEM_IFILESYSTEM_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <FileSystem/IFile.hpp>
#include <string>

namespace AS::Engine {
class ENGINE_EXPORT IFileSystem : public IModule {
 public:
  virtual char* GetGamePath() const = 0;
  virtual char* GetExecutablePath() const = 0;
  virtual char* GetBinPath() const = 0;

  virtual void SetupGamePath(const char* gameDir) = 0;

  virtual IFile* CreateFile() = 0;
  virtual bool FileExists(const char* path, unsigned long pathType) = 0;
  virtual char* GetPath(const char* path, unsigned long pathType) = 0;

  virtual ~IFileSystem() = default;
};
}  // namespace AS::Engine

#endif