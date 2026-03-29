#include <Engine/ConVar.hpp>
#include <Engine/IConsole.hpp>
#include <Modules/Server/Field.hpp>
#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

IEngine* Server::EngineInstance = 0;

void Exit(int argc, char** argv) { Server::GetEngine()->Quit(); }

ConCMD exitCMD("exit", Exit, "Exit");

void Server::OnLoaded() {
  EngineInstance->GetConsole() << "Server starting..." << EndLine;
  EngineInstance->GetConsole().RegisterConCmd(exitCMD);
}
void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() { field.Init(); }
void Server::OnDisabled() { field.Destroy(); }
