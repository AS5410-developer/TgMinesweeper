cmake_minimum_required(VERSION 3.10.0)
project(ASEngine VERSION 0.1.0 LANGUAGES CXX)

include(GenerateExportHeader)

include_directories(include ${CMAKE_BINARY_DIR})
include_directories(include third-party/glm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_link_options(
    -stdlib=libc++
)
add_compile_options(-stdlib=libc++)
link_libraries(c++abi)

add_subdirectory(third-party/httplib)

add_subdirectory(src)

