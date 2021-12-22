#pragma once

#include "posix_socket.h"
#include "ssl_build_flag.h"
#include "ipv6_build_flag.h"

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

#if BUILDFLAG(IPv6)
    bool Init6();
#endif

#if BUILDFLAG(SSL)
    bool InitSSL();
#endif

    void DoRead();

public:
    bool Start();
    void Close();

private:
    PosixSocket socket_;
    std::uint32_t port_{};

#if BUILDFLAG(IPv6)
    PosixSocket v6_socket_;
    std::uint32_t v6_port_{};
#endif

#if BUILDFLAG(SSL)
    PosixSocket ssl_socket_;
    std::uint32_t ssl_port_{};
#endif
};