#ifndef INC_SERVER_FIELD_HPP
#define INC_SERVER_FIELD_HPP

#include <Engine/IEngine.hpp>
#include <Server/IServer.hpp>

#define FIELD_CELL_NONE 0
#define FIELD_CELL_MINE 1
#define FIELD_CELL_FLAG 2
#define FIELD_CELL_OPENED 4
#define FIELD_CELL_IS(x, y) ((x) & (y))

class Field final {
 public:
  Field() {}

  void SetWidth(unsigned char width) { Width = width; }
  void SetHeight(unsigned char height) { Height = height; }
  void SetMineCount(unsigned char count) { MineCount = count; }
  void SetSeed(unsigned long long seed) { Seed = seed; }

  unsigned char GetWidth() { return Width; }
  unsigned char GetHeight() { return Height; }
  unsigned char GetMineCount() { return MineCount; }
  unsigned long long GetSeed() { return Seed; }

  void Init();
  unsigned char GetCell(unsigned char x, unsigned char y);
  bool OpenCell(unsigned char x, unsigned char y);
  void Destroy();

  virtual ~Field() = default;

 private:
  bool Inited = false;
  unsigned char Width = 0;
  unsigned char Height = 0;
  unsigned char MineCount = 0;
  unsigned long long Seed = 0;
  char* Cells = 0;
};

#endif