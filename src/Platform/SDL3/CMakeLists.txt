find_package(SDL3)

add_library(PlatformSDL3 MODULE Entry.cpp Platform.cpp Mutex.cpp Window.cpp)

generate_export_header(PlatformSDL3
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/PlatformSDL3Export.h"
    BASE_NAME PLATFORM_SDL3
)

target_link_libraries(PlatformSDL3 PRIVATE SDL3::SDL3)