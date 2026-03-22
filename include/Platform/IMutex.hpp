#ifndef INC_PLATFORM_IMUTEX_HPP
#define INC_PLATFORM_IMUTEX_HPP

#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <functional>

namespace AS::Engine {
class ENGINE_EXPORT IMutex {
 public:
  virtual void SetResource(void* resource) = 0;
  virtual void StartWorkWithRes(std::function<void(void*)> func) = 0;

  virtual ~IMutex() = default;
};
}  // namespace AS::Engine

#endif