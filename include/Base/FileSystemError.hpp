#ifndef INC_BASE_FILESYSTEMERROR_HPP
#define INC_BASE_FILESYSTEMERROR_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <string>

namespace AS::Engine {
class ENGINE_EXPORT ErrorFileSystem : public IError {
 public:
  ErrorFileSystem(const std::string& error = std::string()) : Error(error) {}
  virtual const std::string What() const override { return Error; }
  virtual bool Failed() const override { return true; };
  virtual IError::LogLevel GetLogLevel() const override {
    return IError::LogLevel::LL_INFO;
  };

  virtual ~ErrorFileSystem() = default;

 private:
  std::string Error;
};
}  // namespace AS::Engine

#endif