#ifndef INC_IKEYBOARD_HPP
#define INC_IKEYBOARD_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <string>
#include <vector>

namespace AS::Engine {
struct Button {
  std::string Text;
  std::string CallbackData;
  bool AddInlineTextToUserMessage = false;
};
using Row = std::initializer_list<Button>;
using RowVec = std::vector<Button>;
class ENGINE_EXPORT IKeyboard {
 public:
  virtual void SetRows(std::initializer_list<Row> rows) = 0;
  virtual void SetRows(std::vector<RowVec> rows) = 0;

  virtual ~IKeyboard() = default;
};
}  // namespace AS::Engine

#endif