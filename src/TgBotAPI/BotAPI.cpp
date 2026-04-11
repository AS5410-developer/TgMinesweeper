#include <Engine/IEngine.hpp>
#include <Modules/TgBotAPI/BotAPI.hpp>
#include <cstring>

using namespace AS::Engine;
IEngine* BotAPI::EngineInstance = 0;
BotAPI* BotAPI::Instance = 0;

void Token(int argc, char** argv) {
  if (argc < 2) {
    if (!BotAPI::GetInstance()->GetToken()) return;
    BotAPI::GetEngine()->GetConsole()
        << BotAPI::GetInstance()->GetToken() << EndLine;
    return;
  }
  BotAPI::GetInstance()->SetToken(argv[1]);
}
void UseWebhook(int argc, char** argv) {
  if (argc < 2) {
    if (!BotAPI::GetInstance()->GetUseWebhook()) return;
    BotAPI::GetEngine()->GetConsole()
        << BotAPI::GetInstance()->GetUseWebhook() << EndLine;
    return;
  }
  if (!strcmp(argv[1], "true") || !strcmp(argv[1], "1")) {
    BotAPI::GetInstance()->SetUseWebhook(true);
    return;
  } else if (!strcmp(argv[1], "false") || !strcmp(argv[1], "0")) {
    BotAPI::GetInstance()->SetUseWebhook(false);
    return;
  }
}
void WebhookURL(int argc, char** argv) {
  if (argc < 2) {
    if (!BotAPI::GetInstance()->GetWebhookURL()) return;
    BotAPI::GetEngine()->GetConsole()
        << BotAPI::GetInstance()->GetWebhookURL() << EndLine;
    return;
  }
  BotAPI::GetInstance()->SetWebhookURL(argv[1]);
}

void Start(int argc, char** argv) {
  if (!BotAPI::GetInstance()->GetToken()) {
    BotAPI::GetEngine()->GetConsole() << "No token set!" << EndLine;
    return;
  }
  BotAPI::GetInstance()->Start();
  BotAPI::GetEngine()->GetConsole() << "Tg started!" << EndLine;
}
void Stop(int argc, char** argv) {
  BotAPI::GetInstance()->Stop();
  BotAPI::GetEngine()->GetConsole() << "Tg stopped!" << EndLine;
}
ConCMD TokenCMD("tg_token", Token, "Set or get tg bot api token");
ConCMD UseWebhookCMD("tg_use_webhook", UseWebhook,
                     "Set or get tg bot api webhook status");
ConCMD WebhookURLCMD("tg_webhook_url", WebhookURL,
                     "Set or get tg bot api webhook URL");
ConCMD StartCMD("tg_start", Start, "Start tg bot api");
ConCMD StopCMD("tg_stop", Stop, "Stop tg bot api");

void BotAPI::OnLoaded() {
  Instance = this;
  handler = new TgBot::Bot("");
  GetEngine()->GetConsole().RegisterConCmd(TokenCMD);
  GetEngine()->GetConsole().RegisterConCmd(UseWebhookCMD);
  GetEngine()->GetConsole().RegisterConCmd(WebhookURLCMD);
  GetEngine()->GetConsole().RegisterConCmd(StartCMD);
  GetEngine()->GetConsole().RegisterConCmd(StopCMD);
}
void BotAPI::Start() {
  if (Runned) return;
  Runned = true;
  handler->getApi().deleteWebhook(true);
  MessagesThreadHandle = std::thread(&BotAPI::MessagesThread, this);
  handler->getEvents().onInlineQuery([&](TgBot::InlineQuery::Ptr query) {
    if (Events)
      EngineInstance->GetServer()->OnInlineRequest(query->id.data(),
                                                   query->query.data());
  });
  handler->getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
    BotAPI::GetEngine()->GetConsole()
        << "Message: " << message->text << EndLine;
    if (Events && message->text[0] == '/')
      EngineInstance->GetServer()->OnCommand(message->text.data());
  });
}
void BotAPI::Stop() {
  if (!Runned) return;
  Runned = false;
  MessagesThreadHandle.join();
}
void BotAPI::OnUpdate() {}
void BotAPI::OnDisabled() { MessagesThreadHandle.join(); }

void BotAPI::SetToken(const char* token) {
  if (Token) delete[] (Token);
  Token = new char[strlen(token) + 1];
  strcpy(Token, token);
  bool runned = Runned;
  if (runned) Stop();
  delete handler;
  handler = new TgBot::Bot(token);
  if (runned) Start();
}

void BotAPI::AddChoose(std::vector<InlineChoose> chooses) {
  if (chooses.empty()) return;
  if (!Token || !Token[0]) return;
  if (!handler) return;
  std::vector<TgBot::InlineQueryResult::Ptr> results;
  for (const auto& choose : chooses) {
    if (!choose.message) continue;
    if (!choose.message->GetText()) continue;

    TgBot::InputTextMessageContent::Ptr input(
        new TgBot::InputTextMessageContent);
    input->messageText = choose.message->GetText();

    TgBot::InlineQueryResultArticle::Ptr article(
        new TgBot::InlineQueryResultArticle);
    article->id = std::to_string(choose.id);
    article->title = choose.title;
    article->replyMarkup =
        ((Message*)choose.message)->GetKeyboard()
            ? ((Message*)choose.message)->GetKeyboard()->GetKeyboardMarkup()
            : nullptr;
    article->description = choose.description;
    article->inputMessageContent = input;

    results.push_back(article);
  }

  handler->getApi().answerInlineQuery(chooses[0].queryID, results);
}
void BotAPI::EditMessage(IMessage* message) {
  if (!message) return;
  if (!message->GetText()) return;
  if (!Token || !Token[0]) return;
  if (!handler) return;

  handler->getApi().editMessageText(
      message->GetText(), ((Message*)message)->GetChatID(), message->GetID(),
      "", "", nullptr,
      ((Message*)message)->GetKeyboard()
          ? ((Message*)message)->GetKeyboard()->GetKeyboardMarkup()
          : nullptr);
}
void BotAPI::MessagesThread() {
  TgBot::TgLongPoll longPoll(*handler);

  // TgBot::TgWebhookTcpServer webhookServer(8080, *handler);
  while (EngineInstance->GetTickrate() != -1 && Runned) {
    if (!Token) return;
    if (!Token[0]) return;

    try {
      if (!UseWebhook) {
        longPoll.start();
      } else {
        // webhookServer.start();
      }
    } catch (std::exception& e) {
      BotAPI::GetEngine()->GetConsole() << "Tg error: " << e.what() << EndLine;
    }
  }
}

void BotAPI::SetUseWebhook(bool enable) {
  UseWebhook = enable;
  if (!handler || !Token) return;
  if (!Token[0]) return;

  if (UseWebhook) {
    handler->getApi().setWebhook(WebhookURL);
  } else {
    handler->getApi().deleteWebhook(true);
  }
}
void BotAPI::SetWebhookURL(const char* url) {
  if (WebhookURL) delete[] (WebhookURL);
  WebhookURL = new char[strlen(url) + 1];
  strcpy(WebhookURL, url);

  if (!handler || !Token) return;
  if (!Token[0]) return;

  handler->getApi().setWebhook(WebhookURL);
}
