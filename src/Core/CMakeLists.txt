set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(core STATIC "")
target_sources(core PRIVATE
    ${CORE_SOURCE_DIR}/Server.cpp
    ${CORE_SOURCE_DIR}/Server.hpp
    ${CORE_SOURCE_DIR}/HttpSession.cpp
    ${CORE_SOURCE_DIR}/HttpSession.hpp
    ${CORE_SOURCE_DIR}/Socket.cpp
    ${CORE_SOURCE_DIR}/Socket.hpp)
target_include_directories(core PUBLIC ${CORE_SOURCE_DIR})

target_link_libraries(core utility)