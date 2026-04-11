#ifndef INC_IBOTAPI_HPP
#define INC_IBOTAPI_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <BotAPI/IKeyboard.hpp>
#include <BotAPI/IMessage.hpp>
#include <BotAPI/IUser.hpp>
#include <string>

namespace AS::Engine {
struct InlineChoose {
  unsigned char id;
  std::string queryID;
  std::string title;
  std::string description;
  IMessage* message;
};
class ENGINE_EXPORT IBotAPI : public IModule {
 public:
  virtual IKeyboard* GetKeyboard() = 0;
  virtual IMessage* GetMessage() = 0;

  virtual void AddChoose(std::vector<InlineChoose> chooses) = 0;
  virtual void EditMessage(IMessage* message) = 0;
  virtual void EditMessageKeyboard(IMessage* message) = 0;
  virtual void AnswerCallback(const char* queryID, const char* message = 0) = 0;

  virtual void SetToken(const char* token) = 0;

  virtual void SetUseWebhook(bool enable) = 0;
  virtual void SetWebhookURL(const char* url) = 0;

  virtual void EnableEvents() = 0;
  virtual void DisableEvents() = 0;

  virtual ~IBotAPI() = default;
};
}  // namespace AS::Engine

#endif