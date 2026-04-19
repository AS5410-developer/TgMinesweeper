#ifndef INC_SERVER_HPP
#define INC_SERVER_HPP

#include <Engine/IEngine.hpp>
#include <Modules/Server/User.hpp>
#include <Server/IServer.hpp>
#include <map>
#include <mutex>

namespace AS::Engine {
class Server : public IServer {
 public:
  Server() { ServerInstance = this; }

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  virtual void OnInlineRequest(const char* queryID, const char* request,
                               std::shared_ptr<IUser> sender) override;
  virtual void OnInlineChosen(const char* queryID, const char* resultID,
                              std::shared_ptr<IUser> sender,
                              std::shared_ptr<IMessage> message) override;
  virtual void OnCommand(const char* command) override;
  virtual void OnNonCommand(const char* message) override {}
  virtual void OnAnyMessage(const char* message) override {}
  virtual void OnCallback(const char* queryID,
                          std::shared_ptr<IMessage> messageId,
                          std::shared_ptr<IUser> user,
                          const char* message) override;

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }
  static Server* GetServer() { return ServerInstance; }

  User* FindUser(UID uid) {
    std::lock_guard<std::recursive_mutex> lock(UserWork);
    if (Users.contains(uid)) return Users[uid];
    return nullptr;
  }
  void CheckIsNew(std::shared_ptr<IUser> tgUser);

  virtual ~Server() = default;

 private:
  static IEngine* EngineInstance;
  static Server* ServerInstance;
  std::recursive_mutex UserWork;
  std::map<UID, User*> Users;
};
}  // namespace AS::Engine

#endif