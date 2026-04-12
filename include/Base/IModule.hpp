#ifndef INC_BASE_IMODULE_HPP
#define INC_BASE_IMODULE_HPP

#include <engine_export.h>

namespace AS::Engine {
class ENGINE_EXPORT IModule {
 public:
  virtual void OnLoaded() = 0;

  virtual void OnRegisterOptions() = 0;
  virtual void OnUpdate() = 0;
  virtual void OnTick() = 0;
  virtual void OnEnabled() = 0;
  virtual void OnDisabled() = 0;
  virtual ~IModule() = default;
};
}  // namespace AS::Engine

#endif