#ifndef INC_PLATFORM_IWINDOW_HPP
#define INC_PLATFORM_IWINDOW_HPP

#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>

#define AS_ENGINE_IWINDOW_SURFACETYPE_OPENGL 0x0000000000000002ULL
#define AS_ENGINE_IWINDOW_SURFACETYPE_VULKAN 0x0000000010000000ULL

namespace AS::Engine {
struct WindowSize {
  unsigned int x;
  unsigned int y;
};
class ENGINE_EXPORT IWindow {
 public:
  virtual void Initialize() = 0;

  virtual void SetSurfaceType(unsigned long long surfaceType) = 0;
  virtual void SetSize(const WindowSize& size) = 0;
  virtual void SetFullscreen(bool isItTrue) = 0;
  virtual void SetTitle(const char* title) = 0;

  virtual WindowSize GetSize() const = 0;
  virtual ResultOrError<void*> GetSurface(void* instance) = 0;
  virtual unsigned long long GetSurfaceType() = 0;
  virtual bool GetFullscreen() = 0;
  virtual const char* GetTitle() = 0;

  virtual bool IsCreated() = 0;

  virtual void Update() = 0;

  virtual void Destroy() = 0;

  virtual ~IWindow() = default;
};
}  // namespace AS::Engine

#endif