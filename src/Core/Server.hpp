#pragma once


#include "Socket.hpp"


class Server
{
public:

    void Init();
    void Close() const;

    // todo: Remove static functions
    static void AcceptHandle(void *data);
    static void SSLAcceptHandle(void *data);

public:

    Server();
    ~Server();

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server &&) = delete;

private:
    Socket fd_{};
    Socket SSL_fd_{};
    std::uint32_t  port_{};
};