add_library(Launcher MODULE Launcher.cpp Entry.cpp)

generate_export_header(Launcher
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/LauncherExport.h"
    BASE_NAME LAUNCHER
)