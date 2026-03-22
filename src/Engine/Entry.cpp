#include <Modules/Engine.hpp>

using namespace AS::Engine;

extern "C" IModule* GetModuleAPI(IEngine* engine) { return new Engine; }