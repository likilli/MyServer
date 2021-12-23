#include <iostream>
#include "server.h"


int main()
{

    int *p = new int;
    *p = 5;
    return 0;

    Server server;
    if (!server.Start())
    {
        std::cerr << "Server start failed" << std::endl;
    }

	std::cout << "hello world" << std::endl;

    return 0;
}
