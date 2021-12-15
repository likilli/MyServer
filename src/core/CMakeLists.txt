add_library(server STATIC "")
target_sources(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h)
target_include_directories(server PUBLIC ${CORE_SOURCE_DIR})

target_link_libraries(server http)