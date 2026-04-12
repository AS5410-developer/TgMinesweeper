#ifndef INC_IUSER_HPP
#define INC_IUSER_HPP

#include <engine_export.h>

#include <Base/IError.hpp>
#include <Base/IModule.hpp>
#include <Base/ResultOrError.hpp>
#include <BotAPI/IKeyboard.hpp>
#include <string>
#include <vector>

namespace AS::Engine {
using UID = long long;
class ENGINE_EXPORT IUser {
 public:
  virtual UID GetID() const = 0;
  virtual const char* GetFirstName() const = 0;
  virtual const char* GetLastName() const = 0;
  virtual const char* GetUserName() const = 0;
  virtual bool IsBot() const = 0;

  virtual ~IUser() = default;
};
}  // namespace AS::Engine
#endif