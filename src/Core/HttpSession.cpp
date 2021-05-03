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
#include "Event.hpp"


constexpr int kBufSize = 4096;

std::string kHeader = "HTTP/1.1 200 OK\r\n"
             "Connection: close\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: 92\r\n"
             "Server:elitk/Manjaro 20.0 - Lysia\r\n"
             "\r\n"
             "<!DOCTYPE html><html><head> Welcom, Kai</head><h1> aaa, elitk's Home page</h1></html>";


HttpSession::HttpSession(const int fd) : socket_(fd)
{

}


HttpSession::~HttpSession()
{
    if (!http_header_.empty())
        http_header_.clear();
}


void HttpSession::Read()
{
    OnRead();
}


void HttpSession::OnRead()
{
    char buf[kBufSize]{};
    ssize_t read_len = recv(socket_.GetFd(), buf, kBufSize - 1, 0);
    if (read_len == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            EventStart(socket_.GetFd(), EventType::Read, [this](){ OnRead(); });
        }
    }

    std::string buffer(buf);
    std::cout << buffer << std::endl;

    EventStop(socket_.GetFd(), EventType::Read);
    Send();
}

void HttpSession::Send()
{
    socket_.SetSendData(kHeader);
    socket_.Send();
}


void HttpSession::Close()
{
    shutdown(socket_.GetFd(), SHUT_RDWR);
    ::close(socket_.GetFd());
}