#include <Modules/TgBotAPI/Keyboard.hpp>

using namespace AS::Engine;

void Keyboard::SetRows(const std::vector<RowVec>& rows) {
  KeyboardMarkup = std::make_shared<TgBot::InlineKeyboardMarkup>();
  for (const auto& row : rows) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    buttons.reserve(row.size());
    for (const auto& button : row) {
      TgBot::InlineKeyboardButton::Ptr btn =
          std::make_shared<TgBot::InlineKeyboardButton>();
      btn->text = button.Text;
      btn->callbackData = button.CallbackData;
      buttons.push_back(btn);
    }
    KeyboardMarkup->inlineKeyboard.push_back(buttons);
  }
  Rows = rows;
}