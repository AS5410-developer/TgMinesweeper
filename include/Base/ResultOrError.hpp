#ifndef INC_BASE_RESULT_OR_ERROR_HPP
#define INC_BASE_RESULT_OR_ERROR_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <string>

namespace AS::Engine {
template <typename T>
class ENGINE_EXPORT ResultOrError : public IError {
 public:
  ResultOrError() {}
  ResultOrError(T result, std::string what = std::string(),
                bool failed = false);

  T& GetResult() { return Result; }

  virtual const std::string What() const override { return TError; }
  virtual bool Failed() const override { return IsFailed; }
  virtual IError::LogLevel GetLogLevel() const override { return Level; }

  virtual operator T() const { return Result; }

  virtual ~ResultOrError() = default;

 private:
  T Result;
  std::string TError;
  bool IsFailed;
  IError::LogLevel Level;
};

template <typename T>
ResultOrError<T>::ResultOrError(T result, std::string what, bool failed)
    : Result(result), TError(what), IsFailed(failed) {}
}  // namespace AS::Engine

#endif