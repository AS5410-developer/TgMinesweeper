#include <Modules/FileSystem/File.hpp>
#include <Modules/FileSystem/FileSystem.hpp>
#include <cstring>
#include <filesystem>
using namespace AS::Engine;

IEngine* FileSystem::EngineInstance = 0;

void FileSystem::OnLoaded() {
  File::SetInstance(this);
#ifdef __linux__
  ExePath = std::string(".");

  auto path = std::filesystem::path(ExePath).append("bin");
  BinPath = path.string();
#endif
}

void FileSystem::SetupGamePath(const char* gameDir) {
#ifdef __linux__
  auto path = std::filesystem::path(ExePath).append(gameDir);
  GamePath = path.string();
#endif
}
std::string FileSystem::GetPath(const char* path, unsigned long pathType) {
  try {
    std::filesystem::path path1;
    if (pathType & AS_ENGINE_FILE_SYSTEM_EXEDIR) {
      path1 = std::filesystem::path(ExePath);
    } else if (pathType & AS_ENGINE_FILE_SYSTEM_BINDIR) {
      path1 = std::filesystem::path(BinPath);
    } else if (pathType & AS_ENGINE_FILE_SYSTEM_GAMEDIR) {
      path1 = std::filesystem::path(GamePath);
    }
    path1 /= path;
    return path1.string();
  } catch (std::exception&) {
    return std::string(path);
  }
  return std::string(path);
}

IFile* FileSystem::CreateFile() { return new File; }
bool FileSystem::FileExists(const char* path, unsigned long pathType) {
  return std::filesystem::exists(GetPath(path, pathType));
}