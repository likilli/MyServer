# library utility
add_library(base STATIC "")
target_sources(base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/event.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/posix_socket.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/posix_socket.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.h)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (ENABLE_SANITIZER)
    target_link_libraries(base asan ubsan)
endif()

add_executable(utils_unittest utils_unittest.cc)
target_link_libraries(utils_unittest base gtest pthread)

add_executable(event_unittest event_unittest.cc)
target_link_libraries(event_unittest base gtest pthread)