#ifndef INC_PLATFORM_IPLATFORM_HPP
#define INC_PLATFORM_IPLATFORM_HPP

#include <Base/IModule.hpp>
#include <Platform/IMutex.hpp>
#include <Platform/IWindow.hpp>

namespace AS::Engine {
typedef WindowSize CursorCoords;
class ENGINE_EXPORT IPlatform : public IModule {
 public:
  virtual ResultOrError<IWindow*> CreateWindow() = 0;

  virtual ResultOrError<IMutex*> CreateMutex() = 0;

  virtual void SetCursorCoords(const CursorCoords& coords) = 0;
  virtual void SetCursorState(bool hide = false) = 0;
  virtual CursorCoords GetCursorCoords() = 0;

  virtual std::vector<char*> GetExtensions() = 0;

  virtual ~IPlatform() = default;
};
}  // namespace AS::Engine

#endif