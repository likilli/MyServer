#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "server.h"
#include "event.h"
#include "http_session.h"


Server::Server()
{
    struct sockaddr_in srv_addr{};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bool ok = false;
    for (uint32_t i = 8000; i < 8100; i++)
    {
        srv_addr.sin_port = htons(i);
        if (bind(socket_.GetSocket(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) == 0)
        {
            port_ = i;
            ok = true;
            std::cout << "[LOG]: Server Running on " << port_ << std::endl;
            break;
        }
    }

    if (!ok)
    {
        std::cerr << "socket bind failed !" << std::endl;
        Close();
    }

    if (listen(socket_.GetSocket(), SOMAXCONN) != 0)
    {
        std::cerr << "listen socket failed " << std::endl;
        Close();
    }
}


Server::~Server()
{
    socket_.StopRead();
}


void Server::Start()
{
    // TODO: fix here, Function Start is blocking!!!
    socket_.StartRead([this](){ DoRead(); });
    EventLoopRun();
    std::cout << "Start here" << std::endl;
}


void Server::DoRead()
{
    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    int cfd = accept(socket_.GetSocket(), (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << "\n[LOG]: Http Request from: " << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(cfd);
    http_session->Start();
}


void Server::Close() const
{
    if (socket_.GetSocket() > 0)
    {
        shutdown(socket_.GetSocket(), SHUT_RDWR);
        ::close(socket_.GetSocket());
    }
}
