#ifndef INC_SERVER_GAME_HPP
#define INC_SERVER_GAME_HPP

#include <Engine/IEngine.hpp>
#include <Modules/Server/Server.hpp>

class Game final {
 public:
  Game() {}

  void Start(const char* queryID,
             std::shared_ptr<AS::Engine::IMessage> messageId,
             std::shared_ptr<AS::Engine::IUser> user);
  void End(const char* queryID, std::shared_ptr<AS::Engine::IMessage> messageId,
           std::shared_ptr<AS::Engine::IUser> user);
  void Win(const char* queryID, std::shared_ptr<AS::Engine::IMessage> messageId,
           std::shared_ptr<AS::Engine::IUser> user);
  void Open(const char* queryID,
            std::shared_ptr<AS::Engine::IMessage> messageId,
            std::shared_ptr<AS::Engine::IUser> user, char x, char y);
  void Clean(User* user, Field* field);

  virtual ~Game() = default;

 private:
};

#endif