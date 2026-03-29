#include <Modules/Server/Field.hpp>
#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

IEngine* Server::EngineInstance = 0;
Field field;

void Server::OnLoaded() {
  EngineInstance->GetConsole() << "Server starting..." << EndLine;
  field.SetWidth(7);
  field.SetHeight(7);
  field.SetChance(7);
  field.SetMineCount(7);
  field.Init();
}
void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() { field.Init(); }
void Server::OnDisabled() { field.Destroy(); }
