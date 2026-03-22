#ifndef INC_FILESYSTEM_DEFAULT_IMPL_FILESYSTEM_HPP
#define INC_FILESYSTEM_DEFAULT_IMPL_FILESYSTEM_HPP

#include <Engine/IEngine.hpp>
#include <FileSystem/IFileSystem.hpp>

namespace AS::Engine {
class FileSystem : public IFileSystem {
 public:
  FileSystem() {}

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override {}
  virtual void OnUpdate() override {}
  virtual void OnTick() override {}
  virtual void OnEnabled() override {}
  virtual void OnDisabled() override {}

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  virtual char* GetGamePath() const override { return GamePath; }
  virtual char* GetExecutablePath() const override { return ExePath; }
  virtual char* GetBinPath() const override { return BinPath; }

  virtual void SetupGamePath(const char* gameDir) override;
  virtual char* GetPath(const char* path, unsigned long pathType) override;

  virtual IFile* CreateFile() override;
  virtual bool FileExists(const char* path, unsigned long pathType) override;

  virtual ~FileSystem() = default;

 private:
  static IEngine* EngineInstance;
  char* GamePath = 0;
  char* ExePath = 0;
  char* BinPath = 0;
};
}  // namespace AS::Engine

#endif