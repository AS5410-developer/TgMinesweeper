#ifndef INC_ENGINE_ICONVAR_HPP
#define INC_ENGINE_ICONVAR_HPP

#include <engine_export.h>

#include <Base/IError.hpp>

namespace AS::Engine {
class IConVar {
 public:
  virtual const std::string GetName() const = 0;
  virtual const std::string GetDescription() const = 0;
  virtual const std::string Get() const = 0;
  virtual void Set(const std::string& value) = 0;

  virtual ~IConVar() = default;
};

}  // namespace AS::Engine
#endif