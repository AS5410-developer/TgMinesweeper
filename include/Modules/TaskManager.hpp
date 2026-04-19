#ifndef INC_TASKMGR_HPP
#define INC_TASKMGR_HPP

#include <engine_export.h>

#include <Engine/IEngine.hpp>
#include <Engine/ITaskManager.hpp>
#include <Modules/Console.hpp>
#include <barrier>
#include <chrono>
#include <condition_variable>
#include <map>
#include <thread>

namespace AS::Engine {

class TaskManager final : public ITaskManager {
 public:
  TaskManager(unsigned char count);

  virtual void AllowExecOnAdd(bool allow = true) override { AutoExec = allow; }

  virtual void AddTask(Task& task) override;

  virtual void ExecuteAll() override;
  virtual void WaitForExecution() override;

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