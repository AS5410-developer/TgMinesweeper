#include <PlatformSDL3Export.h>

#include <Engine/IEngine.hpp>
#include <Modules/SDL3/Platform.hpp>

using namespace AS::Engine;

extern "C" PLATFORM_SDL3_EXPORT IModule* GetModuleAPI(IEngine* engine) {
  Platform::SetEngine(engine);
  return new Platform;
}