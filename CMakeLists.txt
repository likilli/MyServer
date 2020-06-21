cmake_minimum_required(VERSION 3.15)

project(MyServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-g -Wall -Wextra)

add_subdirectory(src)
include_directories(src)