add_library(http
    HttpSession.cpp
    HttpSession.hpp
    Server.cpp
    Server.hpp
    Event.cpp
    Event.hpp
    Core.hpp
)

add_executable(my_server main.cpp)
target_link_libraries(my_server http)