#ifndef INC_ITASKMGR_HPP
#define INC_ITASKMGR_HPP

#include <engine_export.h>

#include <Engine/IEngine.hpp>
#include <Modules/Console.hpp>
#include <barrier>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <map>
#include <thread>

namespace AS::Engine {

using TaskFunc = std::function<void()>;

struct Task {
  TaskFunc Function;
  bool RunNotE;
};

class ITaskManager {
 public:
  virtual void AllowExecOnAdd(bool allow = true) = 0;

  virtual void AddTask(Task& task) = 0;

  virtual void ExecuteAll() = 0;
  virtual void WaitForExecution() = 0;

  virtual ~ITaskManager() = default;
};
}  // namespace AS::Engine

#endif