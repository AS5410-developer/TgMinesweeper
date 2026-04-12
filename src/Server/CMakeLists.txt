
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/minesweeper2D/bin)

add_library(Server MODULE Entry.cpp Server.cpp Field.cpp Game.cpp)

generate_export_header(Server
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/ServerExport.h"
    BASE_NAME SERVER
)