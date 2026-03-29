#include <CtrlUIExport.h>

#include <Engine/IEngine.hpp>
#include <Modules/CtrlUI/CtrlUI.hpp>

using namespace AS::Engine;

extern "C" CTRLUI_EXPORT IModule* GetModuleAPI(IEngine* engine) {
  CtrlUI::SetEngine(engine);
  return new CtrlUI;
}
