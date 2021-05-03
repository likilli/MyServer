add_subdirectory(Core)
add_subdirectory(Utility)

add_executable(my_server main.cpp)
target_link_libraries(my_server core)