#include <Modules/TgBotAPI/User.hpp>

using namespace AS::Engine;

void User::GetDataFrom(TgBot::User::Ptr tgUser) {
  ID = tgUser->id;

  FirstName = new char[strlen(tgUser->firstName.data()) + 1];
  strcpy(FirstName, tgUser->firstName.data());

  if (!tgUser->lastName.empty()) {
    LastName = new char[strlen(tgUser->lastName.data()) + 1];
    strcpy(LastName, tgUser->lastName.data());
  }

  if (!tgUser->username.empty()) {
    UserName = new char[strlen(tgUser->username.data()) + 1];
    strcpy(UserName, tgUser->username.data());
  }

  IsBotFlag = tgUser->isBot;
}