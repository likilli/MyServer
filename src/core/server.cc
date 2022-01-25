#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "server.h"
#include "event.h"
#include "http_session.h"


Server::Server() = default;


Server::~Server()
{
    socket_.StopRead();
}


bool Server::Init()
{
    struct sockaddr_in srv_addr{};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bool bind_ok = false;
    for (uint32_t i = 8000; i < 8100; i++)
    {
        srv_addr.sin_port = htons(i);
        if (bind(socket_.GetSocket(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) == 0)
        {
            port_ = i;
            bind_ok = true;
            std::cout << "[LOG]: Server Running on " << port_ << std::endl;
            break;
        }
    }
    if (!bind_ok)
    {
        std::cerr << "[ERROR] socket bind failed !" << std::endl;
        return false;
    }

    if (listen(socket_.GetSocket(), SOMAXCONN) != 0)
    {
        std::cerr << "[ERROR] listen socket failed " << std::endl;
        return false;
    }

    return true;
}


#if BUILDFLAG(IPv6)
bool Server::Init6()
{
    struct sockaddr_in srv_addr{};

    return true;
}
#endif


#if BUILDFLAG(SSL)
bool Server::InitSSL()
{
    return true;
}
#endif


void Server::DoRead()
{
    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    int cfd = accept(socket_.GetSocket(), (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << "\n[LOG]: Http Request from: " << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(cfd);
    http_session->Start();
}


bool Server::Start()
{
    if (!Init())
    {
        std::cerr << "[ERROR]: Init failed" << std::endl;
        return false;
    }
    socket_.SetOnReadCallback([&](){ DoRead(); });
    socket_.StartRead();

#if BUILDFLAG(IPv6)
    v6_socket_.StartRead([this]() { DoRead(); });
#endif

#if BUILDFLAG(SSL)
    ssl_socket_.StartRead([this](){ DoRead(); });
#endif

    EventLoopRun();

    return true;
}


void Server::Close()
{
    socket_.Close();
}
