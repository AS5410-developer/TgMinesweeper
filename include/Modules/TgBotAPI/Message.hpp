#ifndef INC_MESSAGE_HPP
#define INC_MESSAGE_HPP

#include <engine_export.h>
#include <tgbot/tgbot.h>

#include <BotAPI/IMessage.hpp>
#include <Modules/TgBotAPI/Keyboard.hpp>
namespace AS::Engine {
class Message : public IMessage {
 public:
  Message() : KeyboardD(nullptr) {}

  virtual void SetText(const char* text) override { Text = std::string(text); }
  virtual const char* GetText() const override { return Text.c_str(); }

  virtual void SetKeyboard(IKeyboard* keyboard) override {
    KeyboardD = (Keyboard*)keyboard;
  }
  Keyboard* GetKeyboard() const { return KeyboardD; }
  virtual MID GetID() const override { return ID; }
  void SetID(const MID& id) { ID = id; }
  MID GetChatID() const { return ChatID; }

  bool IsInline() const { return inlineR; }
  void SetInline(bool inlineR) { this->inlineR = inlineR; }

  virtual void GetDataFrom(TgBot::Message::Ptr tgMessage);

  virtual ~Message() = default;

 private:
  std::string Text;
  bool inlineR = false;
  MID ID;
  MID ChatID;
  Keyboard* KeyboardD;
};
}  // namespace AS::Engine

#endif