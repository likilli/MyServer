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

add_executable(utils_unittest utils_unittest.cc)
if (ENABLE_SANITIZER)
    target_link_libraries(utils_unittest asan ubsan base gtest pthread)
else()
    target_link_libraries(utils_unittest base gtest pthread)
endif()

add_executable(event_unittest event_unittest.cc)
if (ENABLE_SANITIZER)
    target_link_libraries(event_unittest asan ubsan base gtest pthread)
else()
    target_link_libraries(event_unittest base gtest pthread)
endif()
