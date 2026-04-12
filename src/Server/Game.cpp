#include <Modules/Server/Game.hpp>

void Game::Start(const char* queryID,
                 std::shared_ptr<AS::Engine::IMessage> messageId,
                 std::shared_ptr<AS::Engine::IUser> user) {
  auto EngineInstance = AS::Engine::Server::GetEngine();
  auto Server = AS::Engine::Server::GetServer();
  auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();
  auto userObj = Server->FindUser(user->GetID());

  EngineInstance->GetBotAPI()->AnswerCallback(queryID);

  Field* field = new Field;
  field->SetWidth(7);
  field->SetHeight(7);
  field->SetMineCount(10);
  field->Init();

  userObj->SetCurrentField(field);
  userObj->SetStatus(USER_STATUS_PLAYING_SINGLE);

  std::vector<std::vector<AS::Engine::Button>> fieldKeyboard;
  for (size_t i = 0; i < field->GetWidth(); i++) {
    std::vector<AS::Engine::Button> row;
    for (size_t j = 0; j < field->GetHeight(); j++) {
      AS::Engine::Button button;
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
  userObj->SetCurrentKeyboard(keyboard);

  messageId->SetText("Разминируйте поле, сапёр. Осталось флагов: 10");
  messageId->SetKeyboard(keyboard);

  EngineInstance->GetBotAPI()->EditMessage(messageId.get());
}

void Game::End(const char* queryID,
               std::shared_ptr<AS::Engine::IMessage> messageId,
               std::shared_ptr<AS::Engine::IUser> user) {
  auto EngineInstance = AS::Engine::Server::GetEngine();
  auto Server = AS::Engine::Server::GetServer();

  EngineInstance->GetBotAPI()->AnswerCallback(queryID, "-левел за трусость");
  auto userObj = Server->FindUser(user->GetID());
  auto keyboard = EngineInstance->GetBotAPI()->GetKeyboard();

  messageId->SetText("беги беги, трус");
  messageId->SetKeyboard(nullptr);
  EngineInstance->GetBotAPI()->EditMessage(messageId.get());

  (*userObj)--;

  Clean(userObj, userObj->GetCurrentField());
}
void Game::Win(const char* queryID,
               std::shared_ptr<AS::Engine::IMessage> messageId,
               std::shared_ptr<AS::Engine::IUser> user) {
  auto EngineInstance = AS::Engine::Server::GetEngine();
  auto Server = AS::Engine::Server::GetServer();
  auto userObj = Server->FindUser(user->GetID());

  messageId->SetText("gj");
  messageId->SetKeyboard(nullptr);
  EngineInstance->GetBotAPI()->EditMessage(messageId.get());

  ++(*userObj);
  Clean(userObj, userObj->GetCurrentField());
}
void Game::Open(const char* queryID,
                std::shared_ptr<AS::Engine::IMessage> messageId,
                std::shared_ptr<AS::Engine::IUser> user, char x, char y) {
  auto EngineInstance = AS::Engine::Server::GetEngine();
  auto Server = AS::Engine::Server::GetServer();
  auto userObj = Server->FindUser(user->GetID());
  auto field = userObj->GetCurrentField();
  auto keyboard = userObj->GetCurrentKeyboard();

  if (!field->IsOpened(x, y)) {
    if (!field->IsFlagged(x, y) &&
        userObj->GetCurrentAction() == USER_ACTION_DIG) {
      if (field->OpenCell(x, y)) {
        messageId->SetText("Минус ноги и руки");
        Clean(userObj, userObj->GetCurrentField());
        messageId->SetKeyboard(0);
        EngineInstance->GetBotAPI()->EditMessage(messageId.get());
        (*userObj)--;
        return;
      } else {
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

          EngineInstance->GetBotAPI()->EditMessageKeyboard(messageId.get());
        }
      }
    } else if (userObj->GetCurrentAction() == USER_ACTION_FLAG) {
      field->Flag(x, y);

      auto rows = keyboard->GetRows();
      if (field->GetCell(x, y) & FIELD_CELL_FLAG) {
        rows[x][y].Text = "\U0001F6A9";
      } else {
        rows[x][y].Text = "*";
      }

      keyboard->SetRows(rows);
      messageId->SetText(
          std::format("Разминируйте поле, сапёр. Осталось флагов: {}",
                      (int)field->GetRemain())
              .c_str());
      messageId->SetKeyboard(keyboard);

      EngineInstance->GetBotAPI()->EditMessage(messageId.get());
    }
  }
  if (field->GetRemain() >= 0 && !field->GetSafeRemain()) {
    Win(queryID, messageId, user);
  }
  EngineInstance->GetBotAPI()->AnswerCallback(queryID);
}

void Game::Clean(User* user, Field* field) {
  user->SetStatus(USER_STATUS_NONE);
  user->SetCurrentMessage(nullptr);
  if (user->GetCurrentKeyboard()) {
    delete user->GetCurrentKeyboard();
    user->SetCurrentKeyboard(0);
  }
  if (field) {
    field->Destroy();
    delete field;
    user->SetCurrentField(0);
  }
}