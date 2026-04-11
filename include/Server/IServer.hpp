#ifndef INC_SERVER_ISERVER_HPP
#define INC_SERVER_ISERVER_HPP

#include <Base/IModule.hpp>
#include <BotAPI/IMessage.hpp>
#include <BotAPI/IUser.hpp>

namespace AS::Engine {
class ENGINE_EXPORT IServer : public IModule {
 public:
  virtual void OnInlineRequest(const char* queryID, const char* request,
                               IUser* sender) = 0;
  virtual void OnInlineChosen(const char* queryID, const char* resultID,
                              IUser* sender, IMessage* message) = 0;
  virtual void OnCommand(const char* command) = 0;
  virtual void OnNonCommand(const char* message) = 0;
  virtual void OnAnyMessage(const char* message) = 0;
  virtual void OnCallback(const char* queryID, IMessage* messageId, IUser* user,
                          const char* message) = 0;

  virtual ~IServer() = default;
};
}  // namespace AS::Engine

#endif