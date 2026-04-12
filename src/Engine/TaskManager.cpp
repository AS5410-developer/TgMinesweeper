#include <Modules/Engine.hpp>
#include <Modules/TaskManager.hpp>

using namespace AS::Engine;

TaskManager::TaskManager(unsigned char count)
    : ExecComplete(count + 1), ThreadNum(count) {
  for (unsigned char i = 0; i < count; ++i) {
    Threads.emplace_back(&TaskManager::WorkerThread, this);
  }
}

void TaskManager::AddTask(Task& task) {
  TEMutex.lock();
  Tasks.push_back(task);
  TEMutex.unlock();
  if (AutoExec) {
    ThreadExecuter.notify_one();
  }
}

void TaskManager::ExecuteAll() {
  if (AutoExec) return;
  TEMutex.lock();
  if (Tasks.empty()) {
    TEMutex.unlock();
    return;
  }
  DontWait = true;
  TEMutex.unlock();
  ThreadExecuter.notify_all();
}
void TaskManager::WaitForExecution() {
  if (!AutoExec && DontWait) {
    ExecComplete.arrive_and_wait();
    DontWait = false;
    TEMutex.lock();
    Tasks.clear();
    TEMutex.unlock();
  }
}
void TaskManager::WorkerThread() {
  for (;;) {
    {
      std::unique_lock<std::mutex> lock(TEMutex);
      ThreadExecuter.wait(
          lock, [this] { return Destroy || !Tasks.empty() || DontWait; });
      if (Destroy && Tasks.empty()) return;
      if (!Tasks.empty()) {
        auto task = Tasks.back();
        Tasks.pop_back();
        lock.unlock();
        task.Function();
      } else {
        lock.unlock();
      }
    }
    if (!AutoExec && DontWait) {
      ExecComplete.arrive_and_wait();
    }
  }
}