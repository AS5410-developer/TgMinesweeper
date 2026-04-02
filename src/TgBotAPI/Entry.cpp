#include <TgBotAPIExport.h>

#include <Engine/IEngine.hpp>
#include <Modules/TgBotAPI/BotAPI.hpp>

using namespace AS::Engine;

extern "C" TGBOTAPI_EXPORT IModule* GetModuleAPI(IEngine* engine) {
  BotAPI::SetEngine(engine);
  return new BotAPI;
}