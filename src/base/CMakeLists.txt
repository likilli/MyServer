# library utility
add_library(base STATIC "")
target_sources(base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EventImpl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/EventImpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Socket.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Socket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
