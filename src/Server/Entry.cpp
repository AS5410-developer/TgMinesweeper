#include <ServerExport.h>

#include <Engine/IEngine.hpp>
#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

extern "C" SERVER_EXPORT IModule* GetModuleAPI(IEngine* engine) {
  Server::SetEngine(engine);
  return new Server;
}