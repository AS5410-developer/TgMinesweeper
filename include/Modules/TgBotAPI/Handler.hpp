#ifndef INC_BOTAPI_HANDLER_HPP
#define INC_BOTAPI_HANDLER_HPP

#include <Modules/TgBotAPI/BotAPI.hpp>
#include <tgbotxx/tgbotxx.hpp>
namespace AS::Engine {
class BotAPI;
class BotHandler : public tgbotxx::Bot {
 public:
  BotHandler(const std::string& token, BotAPI* api)
      : Bot(token), APIInstance(api) {}
  virtual ~BotHandler() = default;

 private:
  BotAPI* APIInstance;
};
}  // namespace AS::Engine
#endif