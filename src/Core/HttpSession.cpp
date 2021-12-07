/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */


#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <cstring>

#include "HttpSession.hpp"
#include "Event.hpp"
#include "Utils.hpp"


constexpr int kBufSize = 4096;
const std::string kHeader = "HTTP/1.1 200 OK\r\n"
             "Connection: close\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: 85\r\n"
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
            EventStart(socket_.GetFd(), READ, [this](){ OnRead(); });
            return;
        }
    }

    if (read_len > 0)
        recv_buffer_.append(buf, read_len);

    if (recv_buffer_.find("\r\n\r\n") != std::string::npos)
    {
        http_header_ = Utils::ParseHttpHeaderFrom(recv_buffer_);
        Utils::Log(0, "Http Header: ");
        Utils::Log(0, http_header_);
        EventStop(socket_.GetFd(), READ);
        Send();
    }
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
