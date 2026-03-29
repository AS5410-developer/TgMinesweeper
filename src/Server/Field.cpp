#include <Modules/Server/Field.hpp>
#include <random>

void Field::Init() {
  if (Inited) return;

  Cells = reinterpret_cast<unsigned char*>(
      calloc(Width * Height, sizeof(unsigned char)));

  if (!Seed) {
    Seed = time(0) * 20 / 5;
  }
  if (!Cells) return;

  std::random_device randomDev;

  std::mt19937 gen(randomDev());

  std::uniform_int_distribution<> distrib(0, GetChance());

  unsigned char CurrentMineCount = 0;

  while (CurrentMineCount < MineCount) {
    for (unsigned char x = 0; x < Width; x++) {
      for (unsigned char y = 0; y < Height; y++) {
        if (CurrentMineCount >= MineCount) break;
        if (distrib(gen) == 0 &&
            !FIELD_CELL_IS(GetCell(x, y), FIELD_CELL_MINE)) {
          SetCell(x, y, FIELD_CELL_MINE);
          CurrentMineCount++;
        }
      }
    }
  }
  Inited = true;
}
bool Field::OpenCell(unsigned char x, unsigned char y) {
  if (!Inited) return false;

  if (FIELD_CELL_IS(GetCell(x, y), FIELD_CELL_MINE)) {
    return true;
  }
  if (!FIELD_CELL_IS(GetCell(x, y), FIELD_CELL_FLAG)) {
    SetCell(x, y, GetCell(x, y) | FIELD_CELL_OPENED);
  }

  return false;
}
void Field::Destroy() {
  if (!Inited) return;
  free(Cells);
  Cells = 0;
  Inited = false;
}