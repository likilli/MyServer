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

private:
    bool Init();

#if defined(ENABLE_IPV6)
    bool Init6();
#endif

#if defined(ENABLE_SSL)
    bool InitSSL();
#endif

    void DoRead();

public:
    bool Start();
    void Close();

private:
    PosixSocket socket_;
    std::uint32_t port_{};

#if defined(ENABLE_IPV6)
    PosixSocket v6_socket_;
    std::uint32_t v6_port_{};
#endif

#if defined(ENABLE_SSL)
    PosixSocket ssl_socket_;
    std::uint32_t ssl_port_{};
#endif
};