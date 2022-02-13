cmake_minimum_required(VERSION 3.20)

project(MyServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INSTALL_NAME_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

# event options
option(USE_SELECT "use select" ON)
option(USE_EPOLL "use epoll" OFF)
option(USE_LIBEVENT "use libevent" OFF)

if (USE_SELECT)
    message(STATUS "[Select]: Enabled")
    add_definitions(-DUSE_SELECT)
endif ()

if (USE_EPOLL)
    message(STATUS "[Epoll]: Enabled")
    add_definitions(-DUSE_EPOLL)
endif()

if (USE_LIBEVENT)
    message(STATUS "[Libevent]: Enabled")
    add_definitions(-DUSE_LIBEVENT)
endif()

# connection options
option(ENABLE_SSL "enable SSL" OFF)
option(ENABLE_IPv6 "enable IPv6" ON)

if (ENABLE_SSL)
    message(STATUS "[SSL]: Enabled")
    add_definitions(-DENABLE_SSL)
endif()

if (ENABLE_IPv6)
    message(STATUS "[IPv6] Enabled")
    add_definitions(-DENABLE_IPv6)
endif()


# saniziter options
option(ENABLE_SANITIZER "enable sanitizer" OFF)
if (ENABLE_SANITIZER)
    message(STATUS "Enable [Sanitizer]")
    add_compile_options(
        -fno-omit-frame-pointer
        -fsanitize=leak
        -fsanitize=address
        -fsanitize=undefined
    )
endif()

# other settings
include(deps/deps.cmake)

add_compile_options(
    -Wall
    -Wextra
    -Wreorder
    -Werror
)

add_subdirectory(src)
