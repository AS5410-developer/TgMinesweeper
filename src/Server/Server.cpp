#include <Engine/ConVar.hpp>
#include <Engine/IConsole.hpp>
#include <Modules/Server/Field.hpp>
#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

IEngine* Server::EngineInstance = 0;
Field field;
ConVar<double> width("ms2d_width", 7.0, "Width of the field");
ConVar<double> height("ms2d_height", 7.0, "Height of the field");
ConVar<double> chance("ms2d_chance", 7.0, "Chance of a cell being a mine");
ConVar<double> mineCount("ms2d_minecount", 7.0, "Number of mines on the field");

void Start(int argc, char** argv) {
  if (mineCount.GetValue() > width.GetValue() * height.GetValue()) {
    Server::GetEngine()->GetConsole()
        << "Mine count cannot be greater than the total number of cells!"
        << EndLine;
    return;
  }
  field.SetWidth(width.GetValue());
  field.SetHeight(height.GetValue());
  field.SetChance(chance.GetValue());
  field.SetMineCount(mineCount.GetValue());
  field.Init();
}
void Stop(int argc, char** argv) { field.Destroy(); }
void Restart(int argc, char** argv) {
  Stop(argc, argv);
  Start(argc, argv);
}
void Exit(int argc, char** argv) { Server::GetEngine()->Quit(); }

ConCMD startCMD("ms2d_start", Start, "Start");
ConCMD stopCMD("ms2d_stop", Stop, "Stop");
ConCMD restartCMD("ms2d_restart", Restart, "Restart");
ConCMD exitCMD("exit", Exit, "Exit");

void Server::OnLoaded() {
  EngineInstance->GetConsole() << "Server starting..." << EndLine;
  field.SetWidth(7);
  field.SetHeight(7);
  field.SetChance(7);
  field.SetMineCount(7);
  field.Init();
  EngineInstance->GetConsole().RegisterConVar(width);
  EngineInstance->GetConsole().RegisterConVar(height);
  EngineInstance->GetConsole().RegisterConVar(chance);
  EngineInstance->GetConsole().RegisterConVar(mineCount);
  EngineInstance->GetConsole().RegisterConCmd(startCMD);
  EngineInstance->GetConsole().RegisterConCmd(stopCMD);
  EngineInstance->GetConsole().RegisterConCmd(restartCMD);
  EngineInstance->GetConsole().RegisterConCmd(exitCMD);
}
void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() { field.Init(); }
void Server::OnDisabled() { field.Destroy(); }
