#include <Base/FileNotFound.hpp>

using namespace AS::Engine;

FileNotFoundError::FileNotFoundError() {}
FileNotFoundError::FileNotFoundError(const std::string& name) {
  if (name.empty()) return;
  Path = name;
}

const std::string FileNotFoundError::What() const {
  return std::string("File \"") + Path + "\" not found!";
}