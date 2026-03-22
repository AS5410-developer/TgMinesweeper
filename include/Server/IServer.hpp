#ifndef INC_SERVER_ISERVER_HPP
#define INC_SERVER_ISERVER_HPP

#include <Base/IModule.hpp>

namespace AS::Engine {
class ENGINE_EXPORT IServer : public IModule {
 public:
  virtual ~IServer() = default;
};
}  // namespace AS::Engine

#endif