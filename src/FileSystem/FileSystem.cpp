#include <Modules/FileSystem/File.hpp>
#include <Modules/FileSystem/FileSystem.hpp>
#include <cstring>
#include <filesystem>
using namespace AS::Engine;

IEngine* FileSystem::EngineInstance = 0;

void FileSystem::OnLoaded() {
  File::SetInstance(this);
#ifdef __linux__
  //  auto path = std::filesystem::canonical("/proc/self/exe").parent_path();

  //  char* exePath = path.string().data();
  const char* exePath = ".";
  ExePath = new char[strlen(exePath)];
  strcpy(ExePath, exePath);

  const char* binPath =
      std::filesystem::path(ExePath).append("bin").string().c_str();
  BinPath = new char[strlen(binPath)];
  strcpy(BinPath, binPath);
#endif
}

void FileSystem::SetupGamePath(const char* gameDir) {
#ifdef __linux__
  auto path = std::filesystem::path(ExePath).append(gameDir);

  char* gamePath = path.string().data();
  GamePath = new char[strlen(gamePath)];
  strcpy(GamePath, gamePath);
#endif
}
char* FileSystem::GetPath(const char* path, unsigned long pathType) {
  try {
    std::filesystem::path pat;
    if (pathType & AS_ENGINE_FILE_SYSTEM_EXEDIR) {
      pat = std::filesystem::path(ExePath);
    } else if (pathType & AS_ENGINE_FILE_SYSTEM_BINDIR) {
      pat = std::filesystem::path(BinPath);
    } else if (pathType & AS_ENGINE_FILE_SYSTEM_GAMEDIR) {
      pat = std::filesystem::path(GamePath);
    }
    pat /= path;
    char* out = new char[pat.string().length()];
    strcpy(out, pat.string().c_str());
    return out;
  } catch (std::exception&) {
    return const_cast<char*>(path);
  }
  return const_cast<char*>(path);
}

IFile* FileSystem::CreateFile() { return new File; }
bool FileSystem::FileExists(const char* path, unsigned long pathType) {
  return std::filesystem::exists(GetPath(path, pathType));
}