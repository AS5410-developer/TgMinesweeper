#include <Base/ErrorSuccess.hpp>
#include <Base/FileSystemError.hpp>
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

void Console::Clean() {
  if (Buffer)
    Buffer->StartWorkWithRes([](void* pointer) {
      if (pointer) delete static_cast<std::string*>(pointer);
    });
}

void Console::RegisterConVar(IConVar& convar) {
  Convars[convar.GetName()] = &convar;
}
void Console::RegisterConCmd(ConCMD& concmd) { Concmds[concmd.Name] = &concmd; }

std::vector<IConVar*> Console::GetConVars() {
  std::vector<IConVar*> convars;
  for (auto& [unused, convar] : Convars) {
    convars.push_back(convar);
  }
  return convars;
}
std::vector<ConCMD*> Console::GetConCmds() {
  std::vector<ConCMD*> concmds;
  for (auto& [unused, concmd] : Concmds) {
    concmds.push_back(concmd);
  }
  return concmds;
}

void Console::UnregisterConVar(const std::string& convar) {
  if (Convars.contains(convar)) Convars.erase(convar);
}
void Console::UnregisterConCmd(const std::string& concmd) {
  if (Concmds.contains(concmd)) Concmds.erase(concmd);
}

void Validate(std::string& arg) {
  // remove spaces
  int16_t spaces = 0;
  spaces = arg.find(" ");
  if (spaces != EOF) do {
      arg.erase(spaces, 1);
    } while ((spaces = arg.find(" ", spaces)) != EOF);
}

const IError* Console::ExecuteCommand(const std::string& command) {
  // check is empty
  if (command.empty()) return new ErrorSuccess;

  unsigned long long pos = 0;
  unsigned long long lastPos = 0;

  // execute all commands in string
  while (command.length() > pos) {
    // read command
    bool quote = 0;
    lastPos = pos;
    unsigned long long i = pos;
    for (; i < command.length(); i++) {
      if (command[i] == '\"') quote = !quote;
      if ((command[i] == ';' || command[i] == '\n') && !quote) {
        pos = i + 1;
        break;
      }
    }
    if (i == command.length())
      pos = i;
    else
      pos = (i < command.length()) ? i + 1 : command.length();
    if (quote) {
      *this << "Syntax error" << EndLine;
      break;
    }
    // parse & execute
    std::string oneCommand = command.substr(lastPos, i - lastPos);
    std::vector<std::string> args;
    std::string arg;

    for (i = 0; i < oneCommand.length(); i++) {
      if (oneCommand[i] == '\"') {
        quote = !quote;
        continue;
      }
      if (std::isspace(static_cast<unsigned char>(oneCommand[i])) && !quote &&
          !arg.empty()) {
        Validate(arg);
        // add
        args.push_back(arg);
        arg.clear();
      } else
        arg += oneCommand[i];
    }
    if (!arg.empty()) {
      Validate(arg);
      args.push_back(arg);
    }

    if (args.empty()) continue;

    if (Convars.contains(std::string(args[0]))) {
      IConVar* convar = Convars[std::string(args[0])];
      if (args.size() == 1) {
        *this << convar->Get() << EndLine;
        continue;
      }
      std::string value;
      for (size_t i = 1; i < args.size(); i++) {
        value.append(args[i]);
        if (i != args.size() - 1) value.append(" ");
      }
      convar->Set(value);
      continue;
    } else if (Concmds.contains(std::string(args[0]))) {
      ConCMD* concmd = Concmds[std::string(args[0])];
      std::vector<char*> c_args;
      for (auto& s : args) c_args.push_back(s.data());
      concmd->Func(c_args.size(), c_args.data());
      continue;
    } else
      *this << "Unknown command or convar: " << args[0] << EndLine;
  }
  return new ErrorSuccess;
}
const IError* Console::Execute(const std::string& filePath) {
  auto file = EngineInstance->GetFileSystem().CreateFile();
  file->Open(filePath.c_str(),
             AS_ENGINE_FILE_SYSTEM_GAMEDIR | AS_ENGINE_FILE_SYSTEM_READ);
  auto result = file->ReadAll();
  file->Close();
  delete file;
  if (result.Failed()) return new ErrorFileSystem(result.What());

  return ExecuteCommand(result.GetResult());
}

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