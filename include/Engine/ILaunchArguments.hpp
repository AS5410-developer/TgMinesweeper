#ifndef INC_ENGINE_ILAUNCHARGUMENTS_HPP
#define INC_ENGINE_ILAUNCHARGUMENTS_HPP

#include <engine_export.h>

#include <Base/ResultOrError.hpp>
#include <string>

namespace AS::Engine {

class ENGINE_EXPORT ILaunchArguments {
 public:
  virtual void RegisterOption(const std::string& name, bool withParameter) = 0;
  virtual bool HasOption(const std::string& name) = 0;
  virtual ResultOrError<std::string> GetStringParameter(
      const std::string& name) = 0;

  virtual ~ILaunchArguments() = default;
};
}  // namespace AS::Engine

#endif