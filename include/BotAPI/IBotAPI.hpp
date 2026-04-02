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
  virtual void SetToken(const char* token) = 0;

  virtual void SetUseWebhook(bool enable) = 0;
  virtual void SetWebhookURL(const char* url) = 0;

  virtual void EnableEvents() = 0;
  virtual void DisableEvents() = 0;

  virtual ~IBotAPI() = default;
};
}  // namespace AS::Engine

#endif