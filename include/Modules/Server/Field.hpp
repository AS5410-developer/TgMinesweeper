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
  void SetChance(unsigned long long chance) { Chance = chance; }

  unsigned char GetWidth() { return Width; }
  unsigned char GetHeight() { return Height; }
  unsigned char GetMineCount() { return MineCount; }
  unsigned long long GetSeed() { return Seed; }
  unsigned long long GetChance() { return Chance; }

  void Init();
  unsigned char GetCell(unsigned char x, unsigned char y) {
    if (!Cells) return 0;
    return Cells[y * Width + x];
  }
  bool OpenCell(unsigned char x, unsigned char y);
  void Destroy();

  virtual ~Field() = default;

 private:
  void SetCell(unsigned char x, unsigned char y, unsigned char cell) {
    if (!Cells) return;
    Cells[y * Width + x] = cell;
  }
  bool Inited = false;
  unsigned char Width = 0;
  unsigned char Height = 0;
  unsigned char MineCount = 0;
  unsigned long long Seed = 0;
  unsigned char* Cells = 0;
  unsigned long long Chance = 0;
};

#endif