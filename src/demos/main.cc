#include <iostream>
#include "server.h"


int main()
{
    Server server;
    if (!server.Start())
    {
        std::cerr << "Server start failed" << std::endl;
    }

	std::cout << "hello world" << std::endl;

    return 0;
}
