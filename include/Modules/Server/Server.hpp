#ifndef INC_SERVER_HPP
#define INC_SERVER_HPP

#include <Engine/IEngine.hpp>
#include <Server/IServer.hpp>

namespace AS::Engine {
class Server : public IServer {
 public:
  Server() {}

  virtual void OnLoaded() override;
  virtual void OnRegisterOptions() override;
  virtual void OnUpdate() override;
  virtual void OnTick() override;
  virtual void OnEnabled() override;
  virtual void OnDisabled() override;

  static void SetEngine(IEngine* engine) { EngineInstance = engine; }
  static IEngine* GetEngine() { return EngineInstance; }

  virtual ~Server() = default;

 private:
  static IEngine* EngineInstance;
};
}  // namespace AS::Engine

#endif