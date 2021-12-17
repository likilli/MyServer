#pragma once

#include "posix_socket.h"

class Server
{
public:
    Server();
    ~Server();

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server &&) = delete;

public:
    void Start();
    void Close() const;

private:
    void DoRead();

private:
    PosixSocket socket_;
    std::uint32_t port_{};
};