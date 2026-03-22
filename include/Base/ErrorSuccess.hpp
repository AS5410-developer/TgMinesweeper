#ifndef INC_BASE_ERRORSUCCESS_HPP
#define INC_BASE_ERRORSUCCESS_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <string>

namespace AS::Engine {
class ENGINE_EXPORT ErrorSuccess : public IError {
 public:
  ErrorSuccess() {}
  virtual const std::string What() const override { return std::string(); }
  virtual bool Failed() const override { return false; };
  virtual IError::LogLevel GetLogLevel() const override {
    return IError::LogLevel::LL_INFO;
  };

  virtual ~ErrorSuccess() = default;
};
}  // namespace AS::Engine

#endif