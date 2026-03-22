#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

IEngine* Server::EngineInstance = 0;

void Server::OnLoaded() {
  EngineInstance->GetConsole() << "Server starting..." << EndLine;
}
void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() {}
void Server::OnDisabled() {}
