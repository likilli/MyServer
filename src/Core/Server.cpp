#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Event.hpp"
#include "Server.hpp"
#include "HttpSession.hpp"


constexpr short kHttpPort = 8080;
constexpr short kHttpsPort = 8443;
constexpr int kMaxListen = 512;


Server::Server()
{
    port_ = 80;
}


Server::~Server()
{
    // Todo: Do not invoke any function in destructor.
    Close();
}


void Server::Init()
{
    struct sockaddr_in srv_addr{};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(kHttpPort);

    if (bind(fd_.GetFd(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
    {
        std::cerr << "fd bind failed !" << std::endl;
        Close();
    }

    if (listen(fd_.GetFd(), kMaxListen) != 0)
    {
        std::cerr << "listen fd failed !" << std::endl;
        Close();
    }

    // HTTPS
    struct sockaddr_in s_srv_addr{};
    s_srv_addr.sin_family = AF_INET;
    s_srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_srv_addr.sin_port = htons(kHttpsPort);

    if (bind(SSL_fd_.GetFd(), (struct sockaddr*)&s_srv_addr, sizeof(s_srv_addr)) != 0)
    {
        std::cerr << "SSL fd bind failed !" << std::endl;
        Close();
    }

    if (listen(SSL_fd_.GetFd(), kMaxListen) != 0)
    {
        std::cerr << "listen SSL fd failed !" << std::endl;
        Close();
    }

    EventStart(fd_.GetFd(), EventType::Read, [this](){ AcceptHandle(this); });
    EventStart(SSL_fd_.GetFd(), EventType::Read, [this](){ SSLAcceptHandle(this); });
}


void Server::AcceptHandle(void *data)
{
    std::cout << __func__  << std::endl;
    auto server = static_cast<Server*>(data);

    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    int cfd = accept(server->fd_.GetFd(), (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(cfd);
    http_session->Read();
}


void Server::SSLAcceptHandle(void *data)
{
    // todo: log enabled by Macro
    std::cout << __func__ << std::endl;
    auto server = static_cast<Server*>(data);

    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    int cfd = accept(server->SSL_fd_.GetFd(), (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(cfd);
    http_session->Read();
}


void Server::Close() const
{
    if (SSL_fd_.GetFd() > 0)
    {
        // Todo: Send SSL Close message.
    }
}