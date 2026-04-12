#include <Modules/TgBotAPI/User.hpp>

using namespace AS::Engine;

void User::GetDataFrom(TgBot::User::Ptr tgUser) {
  ID = tgUser->id;

  FirstName = std::string(tgUser->firstName);

  if (!tgUser->lastName.empty()) {
    LastName = std::string(tgUser->lastName.data());
  }

  if (!tgUser->username.empty()) {
    UserName = std::string(tgUser->username.data());
  }

  IsBotFlag = tgUser->isBot;
}