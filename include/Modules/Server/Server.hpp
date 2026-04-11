#ifndef INC_SERVER_HPP
#define INC_SERVER_HPP

#include <Engine/IEngine.hpp>
#include <Modules/Server/User.hpp>
#include <Server/IServer.hpp>
#include <map>

namespace AS::Engine {
class Server : public IServer {
 public:
  Server() {}

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  virtual void OnInlineRequest(const char* queryID, const char* request,
                               IUser* sender) override;
  virtual void OnInlineChosen(const char* queryID, const char* resultID,
                              IUser* sender, IMessage* message) override;
  virtual void OnCommand(const char* command) override;
  virtual void OnNonCommand(const char* message) override {}
  virtual void OnAnyMessage(const char* message) override {}
  virtual void OnCallback(const char* queryID, IMessage* messageId, IUser* user,
                          const char* message) override;

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  User* FindUser(UID uid) {
    if (Users.contains(uid)) return Users[uid];
    return nullptr;
  }
  void CheckIsNew(IUser* tgUser);

  virtual ~Server() = default;

 private:
  static IEngine* EngineInstance;
  std::map<UID, User*> Users;
};
}  // namespace AS::Engine

#endif