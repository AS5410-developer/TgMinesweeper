#include <ncurses.h>

#include <Modules/CtrlUI/CtrlUI.hpp>
#include <thread>

using namespace AS::Engine;

IEngine* CtrlUI::EngineInstance = 0;
std::string buffer = "";
WINDOW* win;
WINDOW* modulesSubwin;
WINDOW* consoleSubwin;
WINDOW* consoleText;
bool enteringCommand = false;
std::mutex consoleMutex;

void SetModulesSubwinLayout(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, 2, "Modules");
  IEngine* engine = CtrlUI::GetEngine();
  auto modules = engine->GetModules();
  for (size_t i = 0; i < modules.size() && i < LINES - 5; i++) {
    if (modules[i].Name)
      mvwprintw(win, i + 1, 1, "(%llu) %s [%s]", modules[i].ID,
                modules[i].Name->c_str(), modules[i].Activated ? "ON" : "OFF");
  }
  wrefresh(win);
}

void SetConsoleLayout(WINDOW* win, std::string& text) {
  box(win, 0, 0);
  mvwprintw(win, 0, 2, "Console");
  mvwaddnstr(consoleText, 0, 0, text.c_str(), -1);
  wrefresh(win);
}

void SetDefaultWindowLayout(WINDOW* win, WINDOW* modulesSubwin,
                            WINDOW* consoleSubwin) {
  box(win, 0, 0);
  mvwprintw(win, 0, 2, "AS Minesweeper2D - Control UI");
  mvwprintw(win, LINES - 1, 1, "Press F1 to enter command | Press F10 to quit");
  mvwprintw(win, LINES - 2, 1, "Command: ");
  SetModulesSubwinLayout(modulesSubwin);
  SetConsoleLayout(consoleSubwin, buffer);
  wmove(win, LINES - 2, 10);
}

void Handler(const std::string& text) { buffer.append(text); }

void Clear(int argc, char** argv) {
  buffer.clear();
  SetConsoleLayout(consoleSubwin, buffer);
  wrefresh(win);
}
ConCMD clearCMD("con_clear", Clear, "Clear the console");

void CtrlUI::OnLoaded() {
  buffer.clear();
  UIThread = std::thread(&CtrlUI::UIThreadFunc, this);
  EngineInstance->GetConsole().SetFlushHandler(Handler);
  EngineInstance->GetConsole().RegisterConCmd(clearCMD);
}
void CtrlUI::OnRegisterOptions() {}
void CtrlUI::OnUpdate() {}
void CtrlUI::OnTick() {}
void CtrlUI::OnEnabled() {}
void CtrlUI::OnDisabled() {
  if (UIThread.joinable()) UIThread.join();
}

void Init() {
  initscr();
  setlocale(LC_ALL, "");
  raw();
  clear();
  noecho();
  cbreak();
  curs_set(0);
}
void ClearAll() {
  wclear(win);
  wclear(modulesSubwin);
  wclear(consoleSubwin);
  wclear(consoleText);
}
void Destroy() {
  ClearAll();
  delwin(consoleText);
  delwin(consoleSubwin);
  delwin(modulesSubwin);
  delwin(win);
  curs_set(1);
  clrtoeol();
  buffer.shrink_to_fit();
  endwin();
  exit_curses(0);
}

void RecreateConsole() {
  delwin(consoleText);
  delwin(consoleSubwin);
  consoleSubwin = subwin(win, LINES - 3, (COLS / 2) - 1, 1, COLS / 2);
  consoleText = derwin(consoleSubwin, LINES - 5, (COLS / 2) - 3, 1, 1);
  scrollok(consoleText, TRUE);
}
void RefreshAll() {
  consoleMutex.lock();
  ClearAll();
  RecreateConsole();
  wresize(win, LINES, COLS);
  wresize(modulesSubwin, LINES - 3, (COLS / 2) - 1);
  SetDefaultWindowLayout(win, modulesSubwin, consoleSubwin);
  wrefresh(win);
  consoleMutex.unlock();
}

void CtrlUI::UIThreadFunc() {
  Init();
  win = newwin(LINES, COLS, 0, 0);
  modulesSubwin = subwin(win, LINES - 3, (COLS / 2) - 1, 1, 1);
  consoleSubwin = subwin(win, LINES - 3, (COLS / 2) - 1, 1, COLS / 2);
  consoleText = derwin(consoleSubwin, LINES - 5, (COLS / 2) - 3, 1, 1);
  wtimeout(win, 100);
  scrollok(consoleText, TRUE);
  keypad(win, TRUE);
  consoleMutex.lock();
  SetDefaultWindowLayout(win, modulesSubwin, consoleSubwin);
  consoleMutex.unlock();
  refresh();
  wrefresh(win);
  unsigned long long lastBufferSize = 0;
  while (EngineInstance->GetTickrate() != -1) {
    int key = wgetch(win);
    if (key == KEY_RESIZE) {
      RefreshAll();
      //} else if (key == KEY_F(10)) {
    } else if (key == 'q') {
      EngineInstance->Quit();
      break;
      //} else if (key == KEY_F(1)) {
    } else if (key == 'k') {
      wrefresh(win);
      wtimeout(win, -1);
      enteringCommand = true;
      curs_set(1);
      echo();
      char commandBuffer[256];
      mvwgetnstr(win, LINES - 2, 10, commandBuffer, 255);
      noecho();
      curs_set(0);
      enteringCommand = false;
      RefreshAll();
      if (strlen(commandBuffer) <= 0) continue;
      delete EngineInstance->GetConsole().ExecuteCommand(commandBuffer);
      wtimeout(win, 100);
    }

    if (buffer.size() != lastBufferSize) {
      consoleMutex.lock();
      wclear(modulesSubwin);
      SetModulesSubwinLayout(modulesSubwin);
      wrefresh(modulesSubwin);
      wclear(consoleSubwin);
      SetConsoleLayout(consoleSubwin, buffer);
      wrefresh(consoleSubwin);
      lastBufferSize = buffer.size();
      consoleMutex.unlock();
    }
  }
  Destroy();
}