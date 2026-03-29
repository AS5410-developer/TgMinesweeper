#ifndef INC_CTRLUI_HPP
#define INC_CTRLUI_HPP

#include <Engine/IEngine.hpp>
#include <thread>

namespace AS::Engine {
class CtrlUI : public IModule {
 public:
  CtrlUI() {}

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  void UIThreadFunc();

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  virtual ~CtrlUI() = default;

 private:
  static IEngine* EngineInstance;
  std::thread UIThread;
};
}  // namespace AS::Engine

#endif