#ifndef INC_SERVER_USER_HPP
#define INC_SERVER_USER_HPP

#include <Engine/IEngine.hpp>
#include <Modules/Server/Field.hpp>
#include <Server/IServer.hpp>

enum UserStatus {
  USER_STATUS_NONE,
  USER_STATUS_PLAYING_SINGLE,
  USER_STATUS_PLAYING_MULTI,
  USER_STATUS_WAITING,
};
enum UserAction { USER_ACTION_DIG, USER_ACTION_FLAG };

class User final {
 public:
  User() {}
  User(AS::Engine::IUser* tgUser) : TgUser(tgUser) {}

  void SetTgUser(AS::Engine::IUser* user) { TgUser = user; }
  AS::Engine::IUser* GetTgUser() { return TgUser; }

  void SetStatus(UserStatus status) { Status = status; }
  UserStatus GetStatus() { return Status; }

  void SetCurrentField(Field* field) { CurrentField = field; }
  Field* GetCurrentField() { return CurrentField; }

  void SetLevel(unsigned long long level) { Level = level; }
  unsigned long long GetLevel() { return Level; }
  void operator++() { Level++; }
  void operator--(int) { Level--; }

  void SetCurrentKeyboard(AS::Engine::IKeyboard* keyboard) {
    CurrentKeyboard = keyboard;
  }
  AS::Engine::IKeyboard* GetCurrentKeyboard() { return CurrentKeyboard; }

  void SetCurrentAction(UserAction action) { CurrentAction = action; }
  UserAction GetCurrentAction() { return CurrentAction; }

  void SetCurrentMessage(AS::Engine::IMessage* message) {
    CurrentMessage = message;
  }
  AS::Engine::IMessage* GetCurrentMessage() { return CurrentMessage; }

  virtual ~User() = default;

 private:
  AS::Engine::IUser* TgUser;
  UserStatus Status = USER_STATUS_NONE;
  long long Level = 0;
  AS::Engine::IKeyboard* CurrentKeyboard = 0;
  Field* CurrentField = 0;
  UserAction CurrentAction = USER_ACTION_DIG;
  AS::Engine::IMessage* CurrentMessage = 0;
};

#endif