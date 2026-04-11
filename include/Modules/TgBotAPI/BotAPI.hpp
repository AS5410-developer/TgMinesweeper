#ifndef INC_BOTAPI_HPP
#define INC_BOTAPI_HPP

#include <tgbot/tgbot.h>

#include <BotAPI/IBotAPI.hpp>
#include <Modules/Engine.hpp>
#include <Modules/TgBotAPI/Keyboard.hpp>
#include <Modules/TgBotAPI/Message.hpp>
#include <Modules/TgBotAPI/User.hpp>
#include <thread>

namespace AS::Engine {

class BotAPI : public IBotAPI {
 public:
  BotAPI() {}
  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override {}
  virtual void OnUpdate() override;
  virtual void OnTick() override {}
  virtual void OnEnabled() override {}
  virtual void OnDisabled() override;

  virtual IKeyboard* GetKeyboard() override { return new Keyboard; }
  virtual IMessage* GetMessage() override { return new Message; }

  virtual void AddChoose(std::vector<InlineChoose> chooses) override;
  virtual void EditMessage(IMessage* message) override;
  virtual void AnswerCallback(const char* queryID,
                              const char* message = 0) override;

  virtual void SetToken(const char* token) override;
  char* GetToken() { return Token; }

  virtual void SetUseWebhook(bool enable) override;
  virtual void SetWebhookURL(const char* url) override;

  bool GetUseWebhook() { return UseWebhook; }
  char* GetWebhookURL() { return WebhookURL; }
  char* GetToken() const { return Token; }

  void Start();
  void Stop();

  virtual void EnableEvents() override { Events = true; }
  virtual void DisableEvents() override { Events = false; }

  void MessagesThread();

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  static BotAPI* GetInstance() { return Instance; }

  virtual ~BotAPI() = default;

 private:
  static IEngine* EngineInstance;
  std::thread MessagesThreadHandle;
  static BotAPI* Instance;
  TgBot::Bot* handler = 0;
  char* Token = 0;
  char* WebhookURL = 0;
  bool UseWebhook = false;
  bool Runned = false;
  bool Events = false;
};
}  // namespace AS::Engine

#endif