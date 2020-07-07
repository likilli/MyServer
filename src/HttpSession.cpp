/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */

#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

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

    ssize_t read_len = recv(t->fd_, buf, kBufSize - 1, 0);
    std::cout << buf << std::endl;

    EventStop(t->fd_, EventType::Read);
    HttpSession::OnWrite(t);
    //EventStart(t->fd_, EventType::Write, OnWrite, t);

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

void HttpSession::OnWrite(void *data)
{
    char buf[] = "HTTP/1.1 200 OK\r\n"
                 "Connection: close\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Content-Length: 92\r\n"
                 "Server:elitk/Manjaro 20.0 - Lysia\r\n"
                 "\r\n"
                 "<!DOCTYPE html><html><head> Welcom, Kai</head><h1> aaa, elitk's Home page</h1></html>";

    auto t = static_cast<HttpSession*>(data);
    auto send_len = send(t->fd_, buf, strlen(buf), 0);
    std::cout << send_len << std::endl;
    std::cout << strerror(errno) << std::endl;
    if (send_len == static_cast<long>(strlen(buf)))
    {
        shutdown(t->fd_, SHUT_RDWR);
        ::close(t->fd_);
    }
}


void HttpSession::Close() const
{
    shutdown(fd_, SHUT_RDWR);
    ::close(fd_);
}


