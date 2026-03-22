#ifndef INC_SDL3_PLATFORM_HPP
#define INC_SDL3_PLATFORM_HPP

#include <Base/IModule.hpp>
#include <Engine/IEngine.hpp>
#include <Platform/IPlatform.hpp>

namespace AS::Engine {
class Platform : public IPlatform {
 public:
  Platform() {}

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  virtual ResultOrError<IWindow*> CreateWindow() override;
  virtual ResultOrError<IMutex*> CreateMutex() override;

  virtual void SetCursorCoords(const CursorCoords& coords) override;
  virtual void SetCursorState(bool hide = false) override;
  virtual CursorCoords GetCursorCoords() override;

  virtual std::vector<char*> GetExtensions() override;

  virtual ~Platform() = default;

 private:
  static IEngine* EngineInstance;
};
}  // namespace AS::Engine

#endif