#ifndef INC_BOTAPI_HPP
#define INC_BOTAPI_HPP

#include <BotAPI/IBotAPI.hpp>
#include <Modules/TgBotAPI/Handler.hpp>
#include <tgbotxx/tgbotxx.hpp>

namespace AS::Engine {
class BotHandler;
class BotAPI : public IBotAPI {
 public:
  BotAPI() {}
  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override {}
  virtual void OnUpdate() override;
  virtual void OnTick() override {}
  virtual void OnEnabled() override {}
  virtual void OnDisabled() override;

  virtual void SetToken(const char* token) override;
  char* GetToken() { return Token; }

  virtual void SetUseWebhook(bool enable) override;
  virtual void SetWebhookURL(const char* url) override;

  virtual void EnableEvents() override { Events = true; }
  virtual void DisableEvents() override { Events = true; }

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  static BotAPI* GetInstance() { return Instance; }

  virtual ~BotAPI() = default;

 private:
  static IEngine* EngineInstance;
  static BotAPI* Instance;
  BotHandler* handler = 0;
  char* Token = 0;
  bool UseWebhook = false;
  bool Events = false;
};
}  // namespace AS::Engine

#endif