#pragma once


#include "Socket.hpp"


class Server
{
public:
    void Start();
    void Close() const;

    static void AcceptHandle(void *data);

public:

    Server();
    ~Server();

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server &&) = delete;

private:
    Socket fd_{};
    std::uint32_t  port_{};
};