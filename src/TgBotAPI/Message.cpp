#include <Modules/TgBotAPI/Message.hpp>

using namespace AS::Engine;

void Message::GetDataFrom(TgBot::Message::Ptr tgMessage) {
  Text = std::string(tgMessage->text);

  ID = std::to_string(tgMessage->messageId);
  ChatID = tgMessage->chat->id;
  KeyboardD = nullptr;
}