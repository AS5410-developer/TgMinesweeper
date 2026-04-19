#include <Modules/SDL3/Mutex.hpp>

using namespace AS::Engine;

Mutex::Mutex() {}
void Mutex::StartWorkWithRes(std::function<void(void*)> func) {
  std::lock_guard<std::recursive_mutex> lock(Mut);
  if (!Resource) return;
  func(Resource);
}