#include <LauncherExport.h>

#include <Modules/Launcher.hpp>
#include <iostream>

extern "C" LAUNCHER_EXPORT void Launch(int argc, char** argv) {
  std::cout << "Launcher Library started!\nStarting Engine..." << std::endl;
  AS::Engine::Launcher Launcher(argc, argv);
  Launcher.OnRegisterOptions();
  Launcher.OnLoaded();
  if (!Launcher.IsFailed()) {
    Launcher.OnUpdate();
  }
}