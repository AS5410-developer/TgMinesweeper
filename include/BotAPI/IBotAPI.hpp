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

  virtual bool SetUseWebhook(bool enable) = 0;
  virtual bool SetWebhookURL(const char* url) = 0;

  virtual bool EnableEvents() = 0;
  virtual bool DisableEvents() = 0;

  virtual ~IBotAPI() = default;
};
}  // namespace AS::Engine

#endif