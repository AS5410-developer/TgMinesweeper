#ifndef INC_IMESSAGE_HPP
#define INC_IMESSAGE_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <BotAPI/IKeyboard.hpp>
#include <string>
#include <vector>

namespace AS::Engine {
using MID = unsigned long long;
class ENGINE_EXPORT IMessage {
 public:
  virtual void SetText(const char* text) = 0;
  virtual char* GetText() const = 0;

  virtual void SetKeyboard(IKeyboard* keyboard) = 0;
  virtual MID GetID() const = 0;

  virtual ~IMessage() = default;
};
}  // namespace AS::Engine
#endif