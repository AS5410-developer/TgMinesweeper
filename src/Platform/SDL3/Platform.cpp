#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <Modules/SDL3/Mutex.hpp>
#include <Modules/SDL3/Platform.hpp>
#include <Modules/SDL3/Window.hpp>

using namespace AS::Engine;

IEngine* Platform::EngineInstance = 0;

void Platform::OnLoaded() { SDL_Init(SDL_INIT_VIDEO); }
void Platform::OnRegisterOptions() {}
void Platform::OnUpdate() {}
void Platform::OnTick() {}
void Platform::OnEnabled() {}
void Platform::OnDisabled() { SDL_Quit(); }

ResultOrError<IWindow*> Platform::CreateWindow() { return new Window; }
ResultOrError<IMutex*> Platform::CreateMutex() { return new Mutex; }

std::vector<char*> Platform::GetExtensions() {
  uint32_t sdlExtensionCount = 0;
  const char* const* sdlExtensions =
      SDL_Vulkan_GetInstanceExtensions(&sdlExtensionCount);

  std::vector<char*> extensions;
  for (uint32_t i = 0; i < sdlExtensionCount; ++i) {
    extensions.push_back(const_cast<char*>(sdlExtensions[i]));
  }

  return extensions;
}

void Platform::SetCursorCoords(const CursorCoords& coords) {
  SDL_WarpMouseGlobal(coords.x, coords.y);
}
void Platform::SetCursorState(bool hide) {
  if (hide)
    SDL_HideCursor();
  else
    SDL_ShowCursor();
}
CursorCoords Platform::GetCursorCoords() {
  float x, y;
  SDL_GetGlobalMouseState(&x, &y);
  return {(uint)x, (uint)y};
}