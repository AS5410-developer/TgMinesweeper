#ifndef INC_FILESYSTEM_DEFAULT_IMPL_FILE_HPP
#define INC_FILESYSTEM_DEFAULT_IMPL_FILE_HPP

#include <Modules/FileSystem/FileSystem.hpp>
#include <fstream>

namespace AS::Engine {
class File : public IFile {
 public:
  File() {}
  virtual const IError* Open(const char* path, unsigned long flags) override;

  virtual ResultOrError<unsigned long> GetFileSize() override {
    return ResultOrError<unsigned long>(FileSize, "File is not opened!",
                                        !Opened);
  }

  virtual ResultOrError<char*> ReadAll() override;
  virtual ResultOrError<char*> ReadAllFromCurrentPos() override;
  virtual ResultOrError<char*> ReadFromCurrentPos(unsigned long size) override;
  virtual ResultOrError<char*> Read(unsigned long size) override;

  virtual unsigned long GetCurrentPos() override { return CurrentPos; }
  virtual void SetCurrentPos(unsigned long position) override;

  virtual IError* WriteFromCurrentPos(unsigned long size,
                                      const char* data) override;
  virtual IError* WriteFromStart(unsigned long size, const char* data) override;

  virtual void Close() override;
  static void SetInstance(FileSystem* inst) { Instance = inst; }

  virtual ~File() = default;

 private:
  static FileSystem* Instance;
  std::ifstream Input;
  std::ofstream Output;
  bool Opened = false;
  unsigned long FileSize = 0;
  unsigned long CurrentPos = 0;
};
}  // namespace AS::Engine

#endif