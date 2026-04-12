#ifndef INC_TASKMGR_HPP
#define INC_TASKMGR_HPP

#include <engine_export.h>

#include <Engine/IEngine.hpp>
#include <Modules/Console.hpp>
#include <barrier>
#include <chrono>
#include <condition_variable>
#include <map>
#include <thread>

namespace AS::Engine {

using TaskFunc = std::function<void()>;

struct Task {
  TaskFunc Function;
  bool RunNotE;
};

class TaskManager final {
 public:
  TaskManager(unsigned char count);

  void AllowExecOnAdd(bool allow = true) { AutoExec = allow; }

  void AddTask(Task& task);

  void ExecuteAll();
  void WaitForExecution();

  virtual ~TaskManager() {
    Destroy = true;
    ThreadExecuter.notify_all();
    for (auto& a : Threads) {
      if (a.joinable()) a.join();
    }
  }

 private:
  void WorkerThread();
  unsigned char ThreadNum;
  std::barrier<> ExecComplete;
  std::mutex TEMutex;
  std::condition_variable ThreadExecuter;
  std::vector<std::thread> Threads;
  std::vector<Task> Tasks;
  bool DontWait = false;
  bool Destroy = false;
  bool AutoExec = true;
};
}  // namespace AS::Engine

#endif