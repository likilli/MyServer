#pragma once

#include "Event.hpp"

class Server
{
public:

    void Init();
    void Close() const;

    static void AcceptHandle();

public:

    Server();
    ~Server();

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server &&) = delete;

private:

    event e_{};

    int fd_;
    int port_;

};