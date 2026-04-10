#ifndef INC_SERVER_ISERVER_HPP
#define INC_SERVER_ISERVER_HPP

#include <Base/IModule.hpp>

namespace AS::Engine {
class ENGINE_EXPORT IServer : public IModule {
 public:
  virtual void OnInlineRequest(const char* request) = 0;
  virtual void OnCommand(const char* command) = 0;
  virtual void OnNonCommand(const char* message) = 0;
  virtual void OnAnyMessage(const char* message) = 0;
  virtual void OnCallback(const char* message) = 0;

  virtual ~IServer() = default;
};
}  // namespace AS::Engine

#endif