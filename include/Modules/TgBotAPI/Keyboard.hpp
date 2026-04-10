#ifndef INC_KEYBOARD_HPP
#define INC_KEYBOARD_HPP

#include <engine_export.h>
#include <tgbot/tgbot.h>

#include <BotAPI/IKeyboard.hpp>
namespace AS::Engine {
class Keyboard : public IKeyboard {
 public:
  Keyboard() {}
  virtual void SetRows(std::initializer_list<Row> rows) override;
  virtual void SetRows(std::vector<RowVec> rows) override;

  virtual ~Keyboard() = default;

 private:
  TgBot::InlineKeyboardMarkup::Ptr KeyboardMarkup;
};
}  // namespace AS::Engine

#endif