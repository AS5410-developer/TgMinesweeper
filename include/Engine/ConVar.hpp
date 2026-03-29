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

  virtual const std::string Get() const override;
  virtual void Set(const std::string& value) override;

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
template <typename T>
const std::string ConVar<T>::Get() const {
  return std::to_string(Value);
}
template <typename T>
void ConVar<T>::Set(const std::string& value) {
  if constexpr (std::is_same_v<T, double>) {
    Value = std::stod(value);
  } else if constexpr (std::is_same_v<T, std::string>) {
    Value = value;
  }
}

}  // namespace AS::Engine
#endif