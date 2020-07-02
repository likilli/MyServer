#pragma once

#include "Event.hpp"

class Server
{
public:

    void Init();
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

    int fd_;
    int port_;

};