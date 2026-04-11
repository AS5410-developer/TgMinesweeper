#include <Modules/TgBotAPI/Keyboard.hpp>

using namespace AS::Engine;

void Keyboard::SetRows(const std::initializer_list<Row>& rows) {
  KeyboardMarkup =
      TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);
  for (const auto& row : rows) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    for (const auto& button : row) {
      TgBot::InlineKeyboardButton::Ptr btn(new TgBot::InlineKeyboardButton);
      btn->text = button.Text;
      btn->callbackData = button.CallbackData;
      buttons.push_back(btn);
    }
    KeyboardMarkup->inlineKeyboard.push_back(buttons);
  }
  Rows = std::vector<RowVec>(rows.begin(), rows.end());
}

void Keyboard::SetRows(const std::vector<RowVec>& rows) {
  KeyboardMarkup =
      TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);
  for (const auto& row : rows) {
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    for (const auto& button : row) {
      TgBot::InlineKeyboardButton::Ptr btn(new TgBot::InlineKeyboardButton);
      btn->text = button.Text;
      btn->callbackData = button.CallbackData;
      buttons.push_back(btn);
    }
    KeyboardMarkup->inlineKeyboard.push_back(buttons);
  }
  Rows = rows;
}