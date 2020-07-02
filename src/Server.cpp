#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <cstdint>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>

#include "Server.hpp"
#include "HttpSession.hpp"

constexpr int kMaxListen = 512;

Server::Server()
{
    fd_ = socket(PF_INET, SOCK_STREAM, 0);
    if (fd_ <= 0)
    {
        Close();
        std::cerr << "get fd failed !" << std::endl;
    }

    fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);

    port_ = 80;

}

Server::~Server()
{
    if (fd_)
    {
        shutdown(fd_, SHUT_RDWR);
        ::close(fd_);
    }
}

void Server::Init()
{
    struct sockaddr_in srv_addr{};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(8080);

    if (bind(fd_, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
    {
        std::cerr << "fd bind failed !" << std::endl;
        Close();
    }

    if (listen(fd_, kMaxListen) != 0)
    {
        std::cerr << "listen fd failed " << std::endl;
        Close();
    }

    EventStart(fd_, EventType::Read, AcceptHandle,this);
}

void Server::AcceptHandle(void *data)
{
    std::cout << __func__  << std::endl;
    auto server = static_cast<Server*>(data);

    struct sockaddr_in c_adr{};
    socklen_t c_adr_len = sizeof(c_adr);

    int cfd = accept(server->fd_, (struct sockaddr*)&c_adr, &c_adr_len);
    std::cout << inet_ntoa(c_adr.sin_addr) << std::endl;

    auto http_session = new HttpSession(cfd);
    EventStart(http_session->getFd(), EventType::Read, HttpSession::OnRead, http_session);
}

void Server::Close() const
{
    if (fd_ > 0)
    {
        shutdown(fd_, SHUT_RDWR);
        ::close(fd_);
    }
}