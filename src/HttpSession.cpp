/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */

#include <iostream>

#include <unistd.h>
#include <sys/socket.h>

#include "HttpSession.hpp"

constexpr int kBufSize = 4096;

HttpSession::HttpSession(const int fd) : fd_(fd)
{}

HttpSession::~HttpSession()
{
    if (fd_ > 0)
    {
        shutdown(fd_, SHUT_RDWR);
        ::close(fd_);
    }

    if (!http_header_.empty())
        http_header_.clear();
}

int HttpSession::getFd() const
{
    return fd_;
}

void HttpSession::OnRead(void *data)
{
    auto t = static_cast<HttpSession*>(data);
    char buf[kBufSize]{};
    while (true)
    {
        ssize_t read_len = recv(t->fd_, buf, kBufSize - 1, 0);
        std::cout << buf << std::endl;
        if (read_len > 0)
            break;

        /*
        if (read_len == -1)
        {
            //EventStart(t->e_);
        }
        if (read_len == 0)
        {
            std::cout << t->buffer_ << std::endl;
            break;
            exit(0);
        }
        if (read_len > 0)
        {
            std::cout << buf << std::endl;
            t->buffer_ += buf;
        }
         */
    }
}


void HttpSession::Close() const
{
    shutdown(fd_, SHUT_RDWR);
    ::close(fd_);
}


