#ifndef INC_SDL3_MUTEX_HPP
#define INC_SDL3_MUTEX_HPP

#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <Platform/IPlatform.hpp>
#include <functional>
#include <mutex>

namespace AS::Engine {
class Mutex final : public IMutex {
 public:
  Mutex();
  virtual void SetResource(void* resource) override { Resource = resource; }
  virtual void StartWorkWithRes(std::function<void(void*)> func) override;

  virtual ~Mutex() = default;

 private:
  void* Resource;
  std::mutex Mut;
};
}  // namespace AS::Engine

#endif