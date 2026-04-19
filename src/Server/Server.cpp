#include <Engine/ConVar.hpp>
#include <Engine/IConsole.hpp>
#include <Modules/Server/Field.hpp>
#include <Modules/Server/Game.hpp>
#include <Modules/Server/Server.hpp>

using namespace AS::Engine;

IEngine* Server::EngineInstance = 0;
Server* Server::ServerInstance = 0;
Game* game = 0;

void Exit(int argc, char** argv) { Server::GetEngine()->Quit(); }

ConCMD exitCMD("exit", Exit, "Exit");

void Server::OnLoaded() {
  game = new Game;
  EngineInstance->GetConsole() << "Server starting..." << EndLine;
  EngineInstance->GetConsole().RegisterConCmd(exitCMD);
  EngineInstance->GetBotAPI()->EnableEvents();
}

void Server::OnInlineChosen(const char* queryID, const char* resultID,
                            std::shared_ptr<IUser> sender,
                            std::shared_ptr<IMessage> message) {
  if (!sender || !message) return;
  CheckIsNew(sender);
  if (FindUser(sender->GetID())->GetStatus() != USER_STATUS_NONE) return;
  FindUser(sender->GetID())->SetStatus(USER_STATUS_WAITING);
  FindUser(sender->GetID())->SetCurrentMessage(message);
}

void Server::OnInlineRequest(const char* queryID, const char* request,
                             std::shared_ptr<IUser> sender) {
  if (!sender) return;
  CheckIsNew(sender);
  if (FindUser(sender->GetID())->GetStatus() != USER_STATUS_NONE) {
    auto message = EngineInstance->GetBotAPI()->GetMessage();

    message->SetText("Ты уже играешь");
    message->SetKeyboard(nullptr);

    EngineInstance->GetBotAPI()->AddChoose({{.id = 1,
                                             .queryID = queryID,
                                             .title = "Нельзя",
                                             .description = "Ты уже в игре",
                                             .message = message}});
    return;
  }
  auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();
  auto message = EngineInstance->GetBotAPI()->GetMessage();

  keyboard->SetRows({{{"Да", "ready"}, {"Нет", "minus_level"}}});

  message->SetText("Вы собираетесь сыграть в AS Minesweeper2D. Вы готовы?");
  message->SetKeyboard(keyboard);

  EngineInstance->GetBotAPI()->AddChoose(
      {{.id = 1,
        .queryID = queryID,
        .title = "Indev",
        .description = "Play indev minesweeper2D",
        .message = message}});

  EngineInstance->GetBotAPI()->Free(keyboard);
  EngineInstance->GetBotAPI()->Free(message);
}
void Server::OnCallback(const char* queryID,
                        std::shared_ptr<IMessage> messageId,
                        std::shared_ptr<IUser> user, const char* message) {
  if (!user || !messageId) return;
  CheckIsNew(user);
  User* foundUser = static_cast<User*>(FindUser(user->GetID()));

  if (!foundUser) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }
  if (!foundUser->GetCurrentMessage()) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }
  if (!message || !*message) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }
  if (foundUser->GetCurrentMessage()->GetID() != messageId->GetID()) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }

  if (!strcmp(message, "ready") &&
      foundUser->GetStatus() == USER_STATUS_WAITING) {
    game->Start(queryID, messageId, user);
  } else if (!strcmp(message, "minus_level")) {
    game->End(queryID, messageId, user);
  } else if (std::string(message).starts_with("open_") &&
             foundUser->GetStatus() == USER_STATUS_PLAYING_SINGLE) {
    int x, y;
    if (sscanf(message, "open_%d_%d", &x, &y) != 2) {
      EngineInstance->GetBotAPI()->AnswerCallback(queryID,
                                                  "чо сломать хочешь?");
      return;
    }
    if (x < 0 || x >= 256 || y < 0 || y >= 256) {
      EngineInstance->GetBotAPI()->AnswerCallback(queryID,
                                                  "чо сломать хочешь?");
      return;
    }
    game->Open(queryID, messageId, user, (unsigned char)x, (unsigned char)y);

  } else if (std::string(message).starts_with("flag") &&
             foundUser->GetStatus() == USER_STATUS_PLAYING_SINGLE) {
    foundUser->SetCurrentAction(USER_ACTION_FLAG);
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "Вы взяли флаг");
  } else if (std::string(message).starts_with("dig") &&
             foundUser->GetStatus() == USER_STATUS_PLAYING_SINGLE) {
    foundUser->SetCurrentAction(USER_ACTION_DIG);
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "Вы взяли лопату");
  }
}
void Server::OnCommand(const char* command) {
  EngineInstance->GetConsole() << "Executing command: " << command << EndLine;
  std::string str(command);

  if (str.starts_with("/AS5410")) {
    auto pos = str.find(' ');
    if (pos != std::string::npos) {
      auto command = str.substr(pos + 1);
      delete EngineInstance->GetConsole().ExecuteCommand(command);
    }
  }
}
void Server::CheckIsNew(std::shared_ptr<IUser> tgUser) {
  if (!tgUser) return;
  std::lock_guard<std::recursive_mutex> lock(UserWork);
  if (!FindUser(tgUser->GetID())) {
    Users[tgUser->GetID()] = new User(tgUser);
  }
}

void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() {}
void Server::OnDisabled() {
  std::lock_guard<std::recursive_mutex> lock(UserWork);
  for (auto& [id, user] : Users) {
    delete user;
  }
  Users.clear();
  delete game;
}
