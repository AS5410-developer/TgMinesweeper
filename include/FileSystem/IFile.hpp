#ifndef INC_FILESYSTEM_IFILE_HPP
#define INC_FILESYSTEM_IFILE_HPP

#include <FileSystem/IFileSystem.hpp>
#define AS_ENGINE_FILE_SYSTEM_READ 1 << 0
#define AS_ENGINE_FILE_SYSTEM_WRITE 1 << 1
#define AS_ENGINE_FILE_SYSTEM_RAW 1 << 2
#define AS_ENGINE_FILE_SYSTEM_GAMEDIR 1 << 3
#define AS_ENGINE_FILE_SYSTEM_BINDIR 1 << 4
#define AS_ENGINE_FILE_SYSTEM_EXEDIR 1 << 5

namespace AS::Engine {
class ENGINE_EXPORT IFile {
 public:
  virtual const IError* Open(const char* path, unsigned long flags) = 0;

  virtual ResultOrError<unsigned long> GetFileSize() = 0;

  virtual ResultOrError<char*> ReadAll() = 0;
  virtual ResultOrError<char*> ReadAllFromCurrentPos() = 0;
  virtual ResultOrError<char*> ReadFromCurrentPos(unsigned long size) = 0;
  virtual ResultOrError<char*> Read(unsigned long size) = 0;

  virtual unsigned long GetCurrentPos() = 0;
  virtual void SetCurrentPos(unsigned long position) = 0;

  virtual IError* WriteFromCurrentPos(unsigned long size, const char* data) = 0;
  virtual IError* WriteFromStart(unsigned long size, const char* data) = 0;

  virtual void Close() = 0;

  virtual ~IFile() = default;
};
}  // namespace AS::Engine

#endif