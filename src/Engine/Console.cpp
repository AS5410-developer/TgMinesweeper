#include <Base/ErrorSuccess.hpp>
#include <Modules/Console.hpp>
#include <format>

using namespace AS::Engine;

Console::Console(IEngine* engine) {
  EngineInstance = engine;
  if (!engine) return;

  std::string* buffer = new std::string;
  auto res = engine->GetPlatform().CreateMutex();
  if (res.Failed()) {
    engine->QuitOnError(res);
  }
  Buffer = res.GetResult();
  Buffer->SetResource(buffer);
}

void Console::RegisterConVar(IConVar& convar) {
  Convars[convar.GetName()] = &convar;
}
void Console::RegisterConCmd(ConCMD& concmd) { Concmds[concmd.Name] = &concmd; }

const IError* Console::ExecuteCommand(const std::string& command) {
  if (command.empty()) return new ErrorSuccess;
  const char* commandEnd = command.c_str();
  char* oneCommand = new char[512];
  unsigned int size = 0;
  bool sem = 0;
  while (*commandEnd != 0) {
    if (*commandEnd == '\"') {
      sem = !sem;
    }
    oneCommand[size] = *commandEnd;
    commandEnd++;
    size++;
    if (sem) continue;
    if (*commandEnd == ';') break;
  }
  oneCommand[size] = '\0';
  std::vector<char*> args;
  int last = 0;

  for (unsigned int i = 0; i < size; i++) {
    if (oneCommand[i] == '\"') {
      sem = !sem;
      continue;
    }
    if (sem) continue;
    if (oneCommand[i + 1] == ' ' || oneCommand[i + 1] == 0) {
      oneCommand[i + 1] = '\0';
      args.push_back(oneCommand + last);
      last = i + 2;
      ++i;
      continue;
    }
  }

  if (Convars.contains(std::string(args[0]))) {
    IConVar* convar = Convars[std::string(args[0])];
    if (args.size() == 1) {
      *this << convar->Get() << EndLine;
      goto clean;
    }
    std::string value;
    for (size_t i = 1; i < args.size(); i++) {
      value.append(args[i]);
      if (i != args.size() - 1) value.append(" ");
    }
    convar->Set(value);
    goto clean;
  }
  if (Concmds.contains(std::string(args[0]))) {
    ConCMD* concmd = Concmds[std::string(args[0])];
    concmd->Func(args.size(), args.data());
    goto clean;
  }

  *this << "Unknown command or convar: " << args[0] << EndLine;
clean:
  delete[] oneCommand;
  return new ErrorSuccess;
}
const IError* Console::Execute(const std::string& filePath) { return 0; }

IConsole& Console::operator<<(const std::string& text) {
  Buffer->StartWorkWithRes([&text](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(text);
  });
  return *this;
}
IConsole& Console::operator<<(unsigned long long number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(long long number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(unsigned int number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(int number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(unsigned short number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(short number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(unsigned char number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(char number) {
  Buffer->StartWorkWithRes([&number](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(std::to_string(number));
  });
  return *this;
}
IConsole& Console::operator<<(const char* text) {
  Buffer->StartWorkWithRes([&text](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(text);
  });
  return *this;
}
IConsole& Console::operator<<(char* text) {
  Buffer->StartWorkWithRes([&text](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(text);
  });
  return *this;
}
IConsole& Console::operator<<(void* address) {
  std::string s =
      std::format("0x{:08x}", reinterpret_cast<unsigned long long>(address));
  Buffer->StartWorkWithRes([&s](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append(s);
  });
  return *this;
}
IConsole& Console::operator<<(IConsole& (*manipulator)(IConsole&)) {
  manipulator(*this);
  return *this;
}

void Console::NewLine() {
  Buffer->StartWorkWithRes([](void* buffer) {
    if (!buffer) return;
    reinterpret_cast<std::string*>(buffer)->append("\n");
  });
  Flush();
}
void Console::Flush() {
  Buffer->StartWorkWithRes([&](void* buffer) {
    if (!buffer) return;
    std::string* Buffer = reinterpret_cast<std::string*>(buffer);
    // std::cout << Buffer->c_str();
    if (Handler) Handler(*Buffer);
    Buffer->clear();
  });
}
Console::~Console() {}

IConsole& AS::Engine::EndLine(IConsole& console) {
  console.NewLine();
  return console;
}
IConsole& AS::Engine::Flush(IConsole& console) {
  console.Flush();
  return console;
}