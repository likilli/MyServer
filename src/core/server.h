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
    void DoRead();

#if BUILDFLAG(IPv6)
    bool Init6();
    void DoRead6();
#endif

#if BUILDFLAG(SSL)
    bool InitSSL();
#endif

public:
    bool Start();
    void Close();

private:
    PosixSocket socket_;

#if BUILDFLAG(IPv6)
    PosixSocket v6_socket_{true};
#endif

#if BUILDFLAG(SSL)
    PosixSocket ssl_socket_;
#endif

#if BUILDFLAG(IPv6) && BUILDFLAG(SSL)
    PosixSocket v6_ssl_socket_{true};
#endif
};
