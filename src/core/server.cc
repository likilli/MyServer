#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "server.h"
#include "event.h"
#include "http_session.h"


//constexpr short kHTTP  = 80;
constexpr short kTEST  = 8000;
//constexpr short kHTTPS = 443;
//constexpr short kTESTS = 8043;


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
    srv_addr.sin_port = htons(kTEST);
    if (bind(socket_.GetSocket(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
    {
        std::cerr << "[ERROR]: socket bind error! " << std::endl;
        return false;
    }
    std::cout << "[INFO]: IPv4 HTTP Server Running on " << kTEST << std::endl;

    if (listen(socket_.GetSocket(), SOMAXCONN) != 0)
    {
        std::cerr << "[ERROR] listen socket failed " << std::endl;
        return false;
    }

    return true;
}


void Server::DoRead()
{
    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    Socket cfd = accept(socket_.GetSocket(), (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << "\n[LOG]: Http Request from: " << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(PosixSocket(cfd));
    http_session->Start();
}


#if BUILDFLAG(IPv6)
bool Server::Init6()
{
    struct sockaddr_in6 srv_addr{};
    srv_addr.sin6_family = AF_INET6;
    srv_addr.sin6_port = htons(kTEST);
    srv_addr.sin6_addr = in6addr_any;
    if (bind(v6_socket_.GetSocket(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
    {
        std::cerr << "[ERROR]: " << __FUNCTION__ << ", socket bind error! " << std::endl;
        return false;
    }
    std::cout << "[INFO]: IPv6 HTTP Server Running on: " << kTEST << std::endl;

    if (listen(v6_socket_.GetSocket(), SOMAXCONN) != 0)
    {
        std::cerr << "[ERROR]: " << __FUNCTION__ << ", v6 socket listen failed " << std::endl;
        return false;
    }

    return true;
}


void Server::DoRead6()
{
    struct sockaddr_in6 c_addr{};
    socklen_t c_addr_len = sizeof(c_addr);
    Socket cfd = accept(v6_socket_.GetSocket(), (struct sockaddr*)&c_addr, &c_addr_len);

    char buf[64]{};
    inet_ntop(AF_INET6, &c_addr.sin6_addr, buf, 64);
    std::cout << "\n[INFO]: Recv HTTP Request from: " << buf << std::endl;

    auto v6_http_session = new HttpSession(PosixSocket(cfd));
    v6_http_session->Start();
}
#endif


#if BUILDFLAG(SSL)
bool Server::InitSSL()
{
    return true;
}
#endif


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
    if (!Init6())
    {
        std::cerr << "[ERROR]: " << __FUNCTION__ << ", v6 Init failed" << std::endl;
        return false;
    }
    v6_socket_.SetOnReadCallback([&](){ DoRead6();});
    v6_socket_.StartRead();
#endif

#if BUILDFLAG(SSL)
    ssl_socket_.StartRead([this](){ DoRead(); });
#endif

    StartEventLoop();

    return true;
}


void Server::Close()
{
    socket_.Close();
}
