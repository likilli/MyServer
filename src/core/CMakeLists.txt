add_library(server STATIC "")
target_sources(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/server.h)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(server http)