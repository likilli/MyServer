#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Event.hpp"
#include "Server.hpp"
#include "HttpSession.hpp"



constexpr int kMaxListen = 512;


Server::Server()
{
    port_ = 80;
}


Server::~Server()
{
    // todo:
}


void Server::Init()
{
    struct sockaddr_in srv_addr{};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(8081);

    if (bind(fd_.GetFd(), (struct sockaddr*)&srv_addr, sizeof(srv_addr)) != 0)
    {
        std::cerr << "fd bind failed !" << std::endl;
        Close();
    }

    if (listen(fd_.GetFd(), kMaxListen) != 0)
    {
        std::cerr << "listen fd failed " << std::endl;
        Close();
    }

    EventStart(fd_.GetFd(), EventType::Read, [this](){ AcceptHandle(this); });
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


void Server::Close() const
{
    if (fd_.GetFd() > 0)
    {
        shutdown(fd_.GetFd(), SHUT_RDWR);
        ::close(fd_.GetFd());
    }
}