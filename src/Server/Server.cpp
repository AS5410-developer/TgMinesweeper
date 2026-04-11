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
  EngineInstance->GetBotAPI()->EnableEvents();
}

void Server::OnInlineRequest(const char* queryID, const char* request) {
  EngineInstance->GetConsole()
      << "Inline request: " << request << " (ID: " << queryID << ")" << EndLine;

  auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();
  auto message = EngineInstance->GetBotAPI()->GetMessage();

  keyboard->SetRows({{{"Option 1", "callback_1"}, {"Option 2", "callback_2"}},
                     {{"Option 3", "callback_3"}}});

  message->SetText("Indev");
  message->SetKeyboard(keyboard);
  EngineInstance->GetBotAPI()->AddChoose({{.id = 1,
                                           .queryID = queryID,
                                           .title = "Indev",
                                           .description = "Play indev",
                                           .message = message},
                                          {.id = 2,
                                           .queryID = queryID,
                                           .title = "Indev 2",
                                           .description = "Play not indev",
                                           .message = message}});
}
void Server::OnCommand(const char* command) {
  EngineInstance->GetConsole() << "Executing command: " << command << EndLine;
  std::string str(command);

  if (str.starts_with("/AS5410")) {
    auto pos = str.find(' ');
    if (pos != std::string::npos) {
      auto command = str.substr(pos + 1);
      EngineInstance->GetConsole().ExecuteCommand(command);
    }
  }
}

void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() {}
void Server::OnDisabled() {}
