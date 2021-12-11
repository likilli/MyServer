add_library(http STATIC "")
target_sources(http PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/HttpSession.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/HttpSession.h)
target_include_directories(http PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(http base)