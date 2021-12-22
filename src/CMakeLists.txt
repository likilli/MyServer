include_directories(flags)

add_subdirectory(base)
add_subdirectory(core)
add_subdirectory(http)

add_executable(my_server main.cc)
target_link_libraries(my_server server)