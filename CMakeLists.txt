cmake_minimum_required(VERSION 3.15)

project(MyServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(USE_SELECT "use select" ON)
option(USE_EPOLL "use epoll" OFF)
option(USE_LIBEVENT "use libevent" OFF)

if (USE_SELECT)
    message(STATUS "use select as event implementation")
    add_definitions(-DUSE_SELECT)
endif ()

if (USE_EPOLL)
    message(STATUS "use epoll as event implementation")
    add_definitions(-DUSE_EPOLL)
endif()

if (USE_LIBEVENT)
    message(STATUS "use libevent as event implementation")
    add_definitions(-DUSE_LIBEVENT)
endif()


add_compile_options(-Wall -Wextra)

add_subdirectory(src)