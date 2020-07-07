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

char http_header[] = "HTTP/1.1 200 OK\r\n"
             "Connection: close\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: 92\r\n"
             "Server:elitk/Manjaro 20.0 - Lysia\r\n"
             "\r\n"
             "<!DOCTYPE html><html><head> Welcom, Kai</head><h1> aaa, elitk's Home page</h1></html>";

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
    if (read_len == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            EventStart(t->fd_, EventType::Read, OnRead, t);
        }
    }

    std::string buffer(buf);
    if (buffer.find("\r\n\r\n") == std::string::npos)
        return;

    std::cout << buffer << std::endl;

    EventStop(t->fd_, EventType::Read);
    HttpSession::OnWrite(t);
}

void HttpSession::OnWrite(void *data)
{
    auto t = static_cast<HttpSession*>(data);

    ssize_t send_len = send(t->fd_, http_header + t->sent_len_, strlen(http_header), 0);
    if (send_len == -1)
    {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
        {
            EventStart(t->fd_, EventType::Write, OnWrite, t);
        }
    }
    t->sent_len_ += send_len;
    if (t->sent_len_ == static_cast<ssize_t>(strlen(http_header)))
    {
        EventStop(t->fd_, EventType::Write);
        std::cout << "Send Finish" << std::endl;
        shutdown(t->fd_, SHUT_RDWR);
        ::close(t->fd_);
        exit(0);
    }
}


void HttpSession::Close() const
{
    shutdown(fd_, SHUT_RDWR);
    ::close(fd_);
}


