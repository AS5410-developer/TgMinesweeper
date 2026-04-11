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
  virtual char* GetFirstName() const override { return FirstName; }
  virtual char* GetLastName() const override { return LastName; }
  virtual char* GetUserName() const override { return UserName; }
  virtual bool IsBot() const override { return IsBotFlag; }

  virtual void GetDataFrom(TgBot::User::Ptr tgUser);

  virtual ~User() = default;

 private:
  UID ID = 0;
  char* FirstName;
  char* LastName = 0;
  char* UserName = 0;
  bool IsBotFlag = false;
};
}  // namespace AS::Engine

#endif