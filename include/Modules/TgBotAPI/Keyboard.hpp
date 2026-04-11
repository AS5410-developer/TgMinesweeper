#ifndef INC_KEYBOARD_HPP
#define INC_KEYBOARD_HPP

#include <engine_export.h>
#include <tgbot/tgbot.h>

#include <BotAPI/IKeyboard.hpp>
namespace AS::Engine {
class Keyboard : public IKeyboard {
 public:
  Keyboard() {}
  virtual void SetRows(const std::initializer_list<Row>& rows) override;
  virtual void SetRows(const std::vector<RowVec>& rows) override;
  virtual std::vector<RowVec> GetRows() const override { return Rows; }

  TgBot::InlineKeyboardMarkup::Ptr GetKeyboardMarkup() const {
    return KeyboardMarkup;
  }
  virtual ~Keyboard() = default;

 private:
  TgBot::InlineKeyboardMarkup::Ptr KeyboardMarkup = nullptr;
  std::vector<RowVec> Rows;
};
}  // namespace AS::Engine

#endif