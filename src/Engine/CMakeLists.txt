add_library(Engine SHARED FileNotFound.cpp Entry.cpp Engine.cpp Console.cpp TaskManager.cpp)

generate_export_header(Engine
    EXPORT_FILE_NAME "${CMAKE_SOURCE_DIR}/include/engine_export.h"
    BASE_NAME ENGINE
)