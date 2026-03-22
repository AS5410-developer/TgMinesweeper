#ifndef INC_BASE_IERROR_HPP
#define INC_BASE_IERROR_HPP

#include <engine_export.h>

#include <string>

namespace AS::Engine {
class ENGINE_EXPORT IError {
 public:
  enum LogLevel { LL_INFO, LL_WARNING, LL_DEBUG, LL_ERROR, LL_FATAL_ERROR };

  virtual const std::string What() const = 0;
  virtual bool Failed() const = 0;
  virtual LogLevel GetLogLevel() const = 0;

  virtual ~IError() = default;
};
}  // namespace AS::Engine

#endif