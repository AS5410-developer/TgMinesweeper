#ifndef INC_USER_HPP
#define INC_USER_HPP

#include <engine_export.h>
#include <tgbot/tgbot.h>

#include <BotAPI/IUser.hpp>
namespace AS::Engine {
class User : public IUser {
 public:
  User() {}

  virtual UID GetID() const override { return ID; }
  virtual const char* GetFirstName() const override {
    return FirstName.c_str();
  }
  virtual const char* GetLastName() const override { return LastName.c_str(); }
  virtual const char* GetUserName() const override { return UserName.c_str(); }
  virtual bool IsBot() const override { return IsBotFlag; }

  virtual void GetDataFrom(TgBot::User::Ptr tgUser);

  virtual ~User() = default;

 private:
  UID ID = 0;
  std::string FirstName;
  std::string LastName;
  std::string UserName;
  bool IsBotFlag = false;
};
}  // namespace AS::Engine

#endif