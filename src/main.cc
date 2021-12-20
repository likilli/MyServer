#include <iostream>
#include "server.h"


int main()
{
    Server s;
    if (!s.Start())
    {
        std::cerr << "Server start failed" << std::endl;
    }

	std::cout << "hello world" << std::endl;

    return 0;
}
