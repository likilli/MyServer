
include_directories(flags)


add_library(base STATIC "")
target_sources(base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/base/event.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/base/logging.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/base/posix_socket.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/base/utils.cc
)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/base)


add_library(server STATIC "")
target_sources(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/server/http_session.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/server/server.cc
)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/server)
target_link_libraries(server base)



add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demos/main.cc)
target_link_libraries(demo server)


if (ENABLE_SANITIZER)
    target_link_libraries(my_server asan ubsan)
endif()