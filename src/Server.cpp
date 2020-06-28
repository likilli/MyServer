#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <cstdint>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>

#include "Server.hpp"

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
    bool if_bind_ok = false;

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

    e_.fd_         = fd_;
    e_.data_       = this;
    e_.event_type_ = EVENT_READ;
    e_.onCallBack_ = AcceptHandle;

    EventStart(e_);
}

void Server::AcceptHandle()
{
    std::cout << __func__  << "  " << __LINE__ << std::endl;
    exit(1);
}

void Server::Close() const
{
    if (fd_ > 0)
    {
        shutdown(fd_, SHUT_RDWR);
        ::close(fd_);
    }
}