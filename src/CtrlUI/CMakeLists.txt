
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(Curses_FOUND AND NOT TARGET Curses::Curses)
  add_library(Curses::Curses INTERFACE IMPORTED)
  set_target_properties(
    Curses::Curses
    PROPERTIES
      INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
      INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
  )
endif()

add_library(CtrlUI MODULE Entry.cpp CtrlUI.cpp)

generate_export_header(CtrlUI
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/CtrlUIExport.h"
    BASE_NAME CTRLUI
)

target_link_libraries(CtrlUI PRIVATE Curses::Curses)