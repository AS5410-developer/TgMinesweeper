#ifndef INC_ENGINE_ICONSOLE_HPP
#define INC_ENGINE_ICONSOLE_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Engine/IConVar.hpp>
#include <iostream>
#include <sstream>

namespace AS::Engine {
typedef void (*ConsoleFunc)(int argc, char** argv);

struct ConCMD {
  std::string Name;
  ConsoleFunc Func;
  std::string Description;
};

class ENGINE_EXPORT IConsole {
 public:
  typedef void (*FlushHandler)(const std::string&);

  virtual void Clean() = 0;

  virtual void RegisterConVar(IConVar& convar) = 0;
  virtual void RegisterConCmd(ConCMD& concmd) = 0;

  virtual const IError* ExecuteCommand(const std::string& command) = 0;
  virtual const IError* Execute(const std::string& filePath) = 0;

  virtual IConsole& operator<<(const std::string& text) = 0;
  virtual IConsole& operator<<(unsigned long long number) = 0;
  virtual IConsole& operator<<(long long number) = 0;
  virtual IConsole& operator<<(unsigned int number) = 0;
  virtual IConsole& operator<<(int number) = 0;
  virtual IConsole& operator<<(unsigned short number) = 0;
  virtual IConsole& operator<<(short number) = 0;
  virtual IConsole& operator<<(unsigned char number) = 0;
  virtual IConsole& operator<<(char number) = 0;
  virtual IConsole& operator<<(const char* text) = 0;
  virtual IConsole& operator<<(char* text) = 0;
  virtual IConsole& operator<<(void* address) = 0;
  virtual IConsole& operator<<(IConsole& (*manipulator)(IConsole&)) = 0;
  virtual void NewLine() = 0;
  virtual void Flush() = 0;

  virtual void SetFlushHandler(FlushHandler handler) = 0;
  virtual FlushHandler GetFlushHandler() = 0;

  virtual ~IConsole() = default;
};

extern ENGINE_EXPORT IConsole& EndLine(IConsole& console);
extern ENGINE_EXPORT IConsole& Flush(IConsole& console);
}  // namespace AS::Engine

#endif