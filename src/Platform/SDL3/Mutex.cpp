#include <Modules/SDL3/Mutex.hpp>

using namespace AS::Engine;

Mutex::Mutex() {}
void Mutex::StartWorkWithRes(std::function<void(void*)> func) {
  if (!Resource) return;
  if (!Mut.try_lock()) return;
  func(Resource);
  Mut.unlock();
}