#include <Base/ErrorSuccess.hpp>
#include <Base/FileSystemError.hpp>
#include <Modules/FileSystem/File.hpp>

using namespace AS::Engine;
FileSystem* File::Instance = 0;

const IError* File::Open(const char* path, unsigned long flags) {
  std::ios_base::openmode add(0);
  if (flags & AS_ENGINE_FILE_SYSTEM_RAW) {
    add |= std::ios::binary;
  }
  if (flags & AS_ENGINE_FILE_SYSTEM_WRITE) {
    errno = 0;
    Output = std::ofstream(Instance->GetPath(path, flags), add | std::ios::ate);
    if (!Output.is_open())
      return new ErrorFileSystem("Error while opening file!");
    FileSize = Output.tellp();
    Output.seekp(std::ios::beg);
  }
  if (flags & AS_ENGINE_FILE_SYSTEM_READ) {
    auto pat = Instance->GetPath(path, flags);
    errno = 0;
    Input = std::ifstream(pat, add | std::ios::ate);
    if (!Input.is_open())
      return new ErrorFileSystem("Error while opening file!");
    FileSize = Input.tellg();
    Input.seekg(std::ios::beg);
  }
  Opened = true;
  return new ErrorSuccess();
}

ResultOrError<char*> File::ReadAll() {
  if (!Opened) return ResultOrError<char*>(0, "You have not opened file", true);
  char* in = new char[FileSize];
  Input.read(in, FileSize);
  Input.seekg(std::ios::beg);
  return in;
}
ResultOrError<char*> File::ReadAllFromCurrentPos() {
  if (!Opened) return ResultOrError<char*>(0, "You have not opened file", true);
  char* in = new char[FileSize - CurrentPos];
  Input.read(in, FileSize - CurrentPos);
  Input.seekg(std::ios::beg);
  return in;
}
ResultOrError<char*> File::ReadFromCurrentPos(unsigned long size) {
  if (!Opened) return ResultOrError<char*>(0, "You have not opened file", true);
  char* in = new char[size];
  Input.read(in, size);
  CurrentPos += size;
  return in;
}
ResultOrError<char*> File::Read(unsigned long size) {
  if (!Opened) return ResultOrError<char*>(0, "You have not opened file", true);
  char* in = new char[size];
  Input.read(in, size);
  Input.seekg(std::ios::beg);
  return in;
}

void File::SetCurrentPos(unsigned long position) {
  if (!Opened) return;
  Input.seekg(std::ios::beg + position);
  CurrentPos = position;
}

IError* File::WriteFromCurrentPos(unsigned long size, const char* data) {
  if (!Opened) return new ErrorFileSystem("You have not opened file");
  Output.write(data, size);
  CurrentPos += size;
  return new ErrorSuccess;
}
IError* File::WriteFromStart(unsigned long size, const char* data) {
  if (!Opened) return new ErrorFileSystem("You have not opened file");
  CurrentPos = 0;
  Output.seekp(std::ios::beg);
  Output.write(data, size);
  CurrentPos += size;
  return new ErrorSuccess;
}

void File::Close() {
  if (Input.is_open()) Input.close();
  if (Output.is_open()) Output.close();
}