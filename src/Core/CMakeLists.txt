set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(core STATIC "")
target_sources(core PRIVATE
    ${CORE_SOURCE_DIR}/Server.cc
    ${CORE_SOURCE_DIR}/Server.h
    ${CORE_SOURCE_DIR}/HttpSession.cc
    ${CORE_SOURCE_DIR}/HttpSession.h
    ${CORE_SOURCE_DIR}/Socket.cc
    ${CORE_SOURCE_DIR}/Socket.h)
target_include_directories(core PUBLIC ${CORE_SOURCE_DIR})

target_link_libraries(core utility)