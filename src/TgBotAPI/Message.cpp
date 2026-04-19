#include <Modules/TgBotAPI/Message.hpp>

using namespace AS::Engine;

void Message::GetDataFrom(TgBot::Message::Ptr tgMessage) {
  Text = !tgMessage->text.empty() ? tgMessage->text : std::string();

  ID = std::to_string(tgMessage->messageId);
  ChatID =
      tgMessage->chat ? std::to_string(tgMessage->chat->id) : std::string();
  KeyboardD = nullptr;
}