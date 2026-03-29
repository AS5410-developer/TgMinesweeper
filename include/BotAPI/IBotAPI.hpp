#ifndef INC_IBOTAPI_HPP
#define INC_IBOTAPI_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <string>

namespace AS::Engine {
class ENGINE_EXPORT IBotAPI : public IModule {
 public:
  virtual ~IBotAPI() = default;
};
}  // namespace AS::Engine

#endif