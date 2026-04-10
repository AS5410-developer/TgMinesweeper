#ifndef INC_BOTAPI_HPP
#define INC_BOTAPI_HPP

#include <BotAPI/IBotAPI.hpp>
#include <thread>

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

  void MessagesThread();

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  static BotAPI* GetInstance() { return Instance; }

  virtual ~BotAPI() = default;

 private:
  static IEngine* EngineInstance;
  std::thread MessagesThreadHandle;
  static BotAPI* Instance;
  char* Token = 0;
  uint64_t LastUpdate = 0;
  bool UseWebhook = false;
  bool Events = false;
};
}  // namespace AS::Engine

#endif