#include <Modules/TgBotAPI/Message.hpp>

using namespace AS::Engine;

void Message::GetDataFrom(TgBot::Message::Ptr tgMessage) {
  Text = new char[strlen(tgMessage->text.data()) + 1];
  strcpy(Text, tgMessage->text.data());

  ID = tgMessage->messageId;
  ChatID = tgMessage->chat->id;
  KeyboardD = nullptr;
}