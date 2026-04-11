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

void Server::OnInlineChosen(const char* queryID, const char* resultID,
                            IUser* sender, IMessage* message) {
  CheckIsNew(sender);
  if (FindUser(sender->GetID())->GetStatus() != USER_STATUS_NONE) return;
  FindUser(sender->GetID())->SetStatus(USER_STATUS_WAITING);
  FindUser(sender->GetID())->SetCurrentMessage(message);
}

void Server::OnInlineRequest(const char* queryID, const char* request,
                             IUser* sender) {
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
}
void Server::OnCallback(const char* queryID, IMessage* messageId, IUser* user,
                        const char* message) {
  CheckIsNew(user);
  if (!FindUser(user->GetID())->GetCurrentMessage()) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }
  if (FindUser(user->GetID())->GetCurrentMessage()->GetID() !=
      messageId->GetID()) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "не твоя кнопка");
    return;
  }
  if (!strcmp(message, "ready") &&
      FindUser(user->GetID())->GetStatus() == USER_STATUS_WAITING) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID);
    messageId->SetText("Разминируйте поле, сапёр.\nОсталось флагов: 10");
    auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();
    Field* field = new Field;
    field->SetWidth(7);
    field->SetHeight(7);
    field->SetMineCount(10);
    field->Init();
    FindUser(user->GetID())->SetCurrentField(field);
    FindUser(user->GetID())->SetStatus(USER_STATUS_PLAYING_SINGLE);
    std::vector<std::vector<Button>> fieldKeyboard;
    for (size_t i = 0; i < field->GetWidth(); i++) {
      std::vector<Button> row;
      for (size_t j = 0; j < field->GetHeight(); j++) {
        Button button;
        button.Text = "*";
        button.CallbackData =
            "open_" + std::to_string(i) + "_" + std::to_string(j);
        row.push_back(button);
      }
      fieldKeyboard.push_back(row);
    }
    fieldKeyboard.push_back(
        {{"Флаг", "flag"}, {"Сдаться", "minus_level"}, {"Копать", "dig"}});
    keyboard->SetRows(fieldKeyboard);
    FindUser(user->GetID())->SetCurrentKeyboard(keyboard);
    messageId->SetKeyboard(keyboard);
    EngineInstance->GetBotAPI()->EditMessage(messageId);
  } else if (!strcmp(message, "minus_level")) {
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "-левел за трусость");
    auto userObj = FindUser(user->GetID());

    userObj->SetStatus(USER_STATUS_NONE);
    (*userObj)--;
    userObj->SetCurrentMessage(nullptr);

    messageId->SetText("беги беги, трус");
    auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();
    messageId->SetKeyboard(nullptr);
    EngineInstance->GetBotAPI()->EditMessage(messageId);
  } else if (std::string(message).starts_with("open_") &&
             FindUser(user->GetID())->GetStatus() ==
                 USER_STATUS_PLAYING_SINGLE) {
    auto userObj = FindUser(user->GetID());
    auto field = userObj->GetCurrentField();
    int x, y;
    sscanf(message, "open_%d_%d", &x, &y);

    if (userObj->GetCurrentAction() == USER_ACTION_DIG) {
      if (field->OpenCell(x, y)) {
        messageId->SetText("Минус ноги и руки");
        userObj->SetStatus(USER_STATUS_NONE);
        userObj->SetCurrentMessage(nullptr);
        delete field;
        messageId->SetKeyboard(nullptr);
        (*userObj)--;
        EngineInstance->GetBotAPI()->EditMessage(messageId);
      } else {
        auto keyboard = userObj->GetCurrentKeyboard();
        auto rows = keyboard->GetRows();
        char minesAround = field->GetMinesCountAround(x, y);
        if (rows[x][y].Text == "*") {
          if (minesAround > 0) {
            rows[x][y].Text = std::to_string(minesAround);
          } else {
            rows[x][y].Text = ".";
          }

          keyboard->SetRows(rows);
          messageId->SetKeyboard(keyboard);
          EngineInstance->GetBotAPI()->EditMessageKeyboard(messageId);
        }
      }
    } else {
      field->Flag(x, y);
      if (field->GetRemainReal() != 0 && field->GetRemain() != 0) {
        auto keyboard = userObj->GetCurrentKeyboard();
        auto rows = keyboard->GetRows();
        if (field->GetCell(x, y) & FIELD_CELL_FLAG) {
          rows[x][y].Text = "\U0001F6A9";
        } else {
          rows[x][y].Text = "*";
        }
        keyboard->SetRows(rows);
        messageId->SetText(
            std::format("Разминируйте поле, сапёр.\nОсталось флагов: {}",
                        (int)field->GetRemain())
                .c_str());
        messageId->SetKeyboard(keyboard);
      } else {
        messageId->SetText("gj");
        messageId->SetKeyboard(nullptr);
        userObj->SetStatus(USER_STATUS_NONE);
        userObj->SetCurrentMessage(nullptr);
        ++(*userObj);
        delete field;
      }
      EngineInstance->GetBotAPI()->EditMessage(messageId);
    }
    EngineInstance->GetBotAPI()->AnswerCallback(queryID);
  } else if (std::string(message).starts_with("flag") &&
             FindUser(user->GetID())->GetStatus() ==
                 USER_STATUS_PLAYING_SINGLE) {
    FindUser(user->GetID())->SetCurrentAction(USER_ACTION_FLAG);
    EngineInstance->GetBotAPI()->AnswerCallback(queryID, "Вы взяли флаг");
  } else if (std::string(message).starts_with("dig") &&
             FindUser(user->GetID())->GetStatus() ==
                 USER_STATUS_PLAYING_SINGLE) {
    FindUser(user->GetID())->SetCurrentAction(USER_ACTION_DIG);
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
      EngineInstance->GetConsole().ExecuteCommand(command);
    }
  }
}
void Server::CheckIsNew(IUser* tgUser) {
  if (!FindUser(tgUser->GetID())) {
    Users[tgUser->GetID()] = new User(tgUser);
  }
}

void Server::OnRegisterOptions() {}
void Server::OnUpdate() {}
void Server::OnTick() {}
void Server::OnEnabled() {}
void Server::OnDisabled() {}
