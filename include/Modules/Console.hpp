#ifndef INC_ENGINE_CONSOLE_HPP
#define INC_ENGINE_CONSOLE_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Engine/IConVar.hpp>
#include <Engine/IConsole.hpp>
#include <Engine/IEngine.hpp>
#include <Platform/IMutex.hpp>
#include <map>

namespace AS::Engine {
class IEngine;

class ENGINE_EXPORT Console final : public IConsole {
 public:
  Console() {}
  Console(IEngine* engine);

  virtual void Clean() override;

  virtual void RegisterConVar(IConVar& convar) override;
  virtual void RegisterConCmd(ConCMD& concmd) override;

  virtual const IError* ExecuteCommand(const std::string& command) override;
  virtual const IError* Execute(const std::string& filePath) override;

  virtual IConsole& operator<<(const std::string& text) override;
  virtual IConsole& operator<<(unsigned long long number) override;
  virtual IConsole& operator<<(long long number) override;
  virtual IConsole& operator<<(unsigned int number) override;
  virtual IConsole& operator<<(int number) override;
  virtual IConsole& operator<<(unsigned short number) override;
  virtual IConsole& operator<<(short number) override;
  virtual IConsole& operator<<(unsigned char number) override;
  virtual IConsole& operator<<(char number) override;
  virtual IConsole& operator<<(const char* text) override;
  virtual IConsole& operator<<(char* text) override;
  virtual IConsole& operator<<(void* address) override;
  virtual IConsole& operator<<(IConsole& (*manipulator)(IConsole&)) override;
  virtual void NewLine() override;
  virtual void Flush() override;

  virtual void SetFlushHandler(FlushHandler handler) override {
    this->Handler = handler;
  }
  virtual FlushHandler GetFlushHandler() override { return Handler; }

  virtual ~Console();

 private:
  IEngine* EngineInstance = 0;
  IMutex* Buffer = 0;
  IMutex* Output = 0;
  std::map<std::string, IConVar*> Convars;
  std::map<std::string, ConCMD*> Concmds;
  FlushHandler Handler = 0;
};
}  // namespace AS::Engine

#endif