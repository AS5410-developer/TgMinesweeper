
#include <iostream>

typedef void (*LaunchFunc)(int argc, char** argv);

#ifdef __linux__
#include <dlfcn.h>
int LoadLauncher(int argc, char** argv) {
  void* Lib = dlopen("./bin/libLauncher.so", RTLD_NOW | RTLD_GLOBAL);
  if (!Lib) {
    std::cerr << "Launcher fatal error: cannot load launcher library"
              << std::endl;
    return 1;
  }

  LaunchFunc Entry = reinterpret_cast<LaunchFunc>(dlsym(Lib, "Launch"));

  if (!Entry) {
    std::cerr << "Launcher fatal error: cannot get \"Launch\" symbol from "
                 "loaded launcher library!\ndlerror(): "
              << dlerror() << std::endl;
    return 1;
  }

  Entry(argc, argv);

  dlclose(Lib);

  std::cout << "Successful finish!\n";
  return 0;
}
#endif

int main(int argc, char** argv) {
  std::cout << "ASEngine by AS5410.\n";

  return LoadLauncher(argc, argv);
}
