# library utility
add_library(base STATIC "")
target_sources(base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EventImpl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/EventImpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PosixSocket.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/PosixSocket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(utils_unittest utils_unittest.cc)
target_link_libraries(utils_unittest base)