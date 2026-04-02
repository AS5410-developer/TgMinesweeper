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

ConCMD TokenCMD("tg_token", Token, "Set or get tg bot api token");

void BotAPI::OnLoaded() {
  Instance = this;
  GetEngine()->GetConsole().RegisterConCmd(TokenCMD);
}
void BotAPI::OnUpdate() {}
void BotAPI::OnDisabled() {}

void BotAPI::SetToken(const char* token) {
  if (Token) delete[] (Token);
  Token = new char[strlen(token) + 1];
  strcpy(Token, token);
}

void BotAPI::SetUseWebhook(bool enable) {}
void BotAPI::SetWebhookURL(const char* url) {}
