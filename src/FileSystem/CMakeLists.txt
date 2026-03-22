add_library(FileSystem MODULE Entry.cpp FileSystem.cpp File.cpp)

generate_export_header(FileSystem
    EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/FileSystemExport.h"
    BASE_NAME FILESYSTEM
)