#ifndef INC_ENGINE_CONVAR_HPP
#define INC_ENGINE_CONVAR_HPP

#include <engine_export.h>

#include <Engine/IConVar.hpp>
#include <concepts>

namespace AS::Engine {
template <typename T>
class ConVar : public IConVar {
 public:
  ConVar(const std::string& name, const T& defaultValue,
         const std::string& description = "");

  virtual const std::string GetName() const override;
  virtual const std::string GetDescription() const override;
  T GetValue() const;
  void SetValue(const T& newValue);

  virtual ~ConVar() = default;

 private:
  std::string Name;
  std::string Description;
  T Value;
};

template <typename T>
ConVar<T>::ConVar(const std::string& name, const T& defaultValue,
                  const std::string& description = "")
    : Name(name), Description(description), Value(defaultValue) {
  static_assert(
      std::is_same<T, double>::value || std::is_same<std::string>::value,
      "Are you stupid? ONLY DOUBLE OR STRING!");
}

template <typename T>
const std::string ConVar<T>::GetName() const {
  return Name;
}
template <typename T>
const std::string ConVar<T>::GetDescription() const {
  return Description;
}
template <typename T>
T ConVar<T>::GetValue() const {
  return Value;
}
template <typename T>
void ConVar<T>::SetValue(const T& newValue) {
  Value = newValue;
}

}  // namespace AS::Engine
#endif