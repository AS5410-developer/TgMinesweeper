#ifndef INC_SDL3_WINDOW_HPP
#define INC_SDL3_WINDOW_HPP

#include <SDL3/SDL.h>

#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <Platform/IWindow.hpp>

namespace AS::Engine {
class Window : public IWindow {
 public:
  Window() {}

  virtual void Initialize() override;

  virtual void SetSurfaceType(unsigned long long surfaceType) override {
    Flag = surfaceType;
  }
  virtual void SetSize(const WindowSize& size) override;
  virtual void SetFullscreen(bool isItTrue) override;
  virtual void SetTitle(const char* title) override;

  virtual WindowSize GetSize() const override { return Size; }
  virtual ResultOrError<void*> GetSurface(void* instance) override;
  virtual unsigned long long GetSurfaceType() override { return Flag; }
  virtual bool GetFullscreen() override { return Fullscreen; }
  virtual const char* GetTitle() override { return Title; }

  virtual bool IsCreated() override { return window; }

  virtual void Update() override;

  virtual void Destroy() override;

  virtual ~Window();

 private:
  unsigned long long Flag = 0;
  SDL_Window* window = 0;
  bool InitializedSDL = false;
  bool Fullscreen = false;
  WindowSize Size;
  const char* Title;
};
}  // namespace AS::Engine

#endif