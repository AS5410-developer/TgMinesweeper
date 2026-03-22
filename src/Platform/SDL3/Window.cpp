#include <SDL3/SDL_vulkan.h>

#include <Modules/SDL3/Platform.hpp>
#include <Modules/SDL3/Window.hpp>

using namespace AS::Engine;

void Window::Initialize() {
  window = SDL_CreateWindow(Title, Size.x, Size.y, Flag | SDL_WINDOW_RESIZABLE);
  SDL_ShowWindow(window);
}

void Window::SetSize(const WindowSize& size) {
  Size = size;
  if (!window) return;
  SDL_SetWindowSize(window, size.x, size.y);
}
void Window::SetFullscreen(bool isItTrue) {
  Fullscreen = isItTrue;
  if (window) SDL_SetWindowFullscreen(window, isItTrue);
}
void Window::SetTitle(const char* title) {
  if (window) SDL_SetWindowTitle(window, title);
  Title = title;
}

ResultOrError<void*> Window::GetSurface(void* instance) {
  if (!window) return ResultOrError<void*>(0, "Window = 0", true);
  if (Flag != AS_ENGINE_IWINDOW_SURFACETYPE_VULKAN)
    return ResultOrError<void*>(0,
                                "You trying get surface for OPENGL??? Are you "
                                "serious??? This is only vulkan function!!!",
                                true);
  if (!instance) return ResultOrError<void*>(0, "Why instance is 0?", true);
  VkSurfaceKHR surface = 0;
  SDL_Vulkan_CreateSurface(window, reinterpret_cast<VkInstance>(instance), 0,
                           &surface);
  return surface;
}

void Window::Update() {
  if (!window) return;
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_EVENT_QUIT:
        Destroy();
        Platform::GetEngine()->Quit();
        break;
      case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        int x, y;
        Size.x = e.window.data1;
        Size.y = e.window.data2;
        break;
      default:
        break;
    }
  }
}

void Window::Destroy() {
  if (window) SDL_DestroyWindow(window);
}

Window::~Window() {
  if (window) Destroy();
}