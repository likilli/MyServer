#include <iostream>
#include <csignal>
#include "server.h"


void StopOnSignal(int signal)
{
    std::cout << "[INFO]: Receive signal: " << signal << std::endl;
}


int main()
{
    if (signal(SIGINT, StopOnSignal) == SIG_ERR) {
        std::cout << "[INFO]: Set SIGINT Failed." << std::endl;
    }
    if (signal(SIGTERM, StopOnSignal) == SIG_ERR) {
        std::cout << "[INFO]: Set SIGTERM Failed. " << std::endl;
    }

    Server server;
    if (!server.Start())
        std::cerr << "Server start failed" << std::endl;

    return 0;
}
