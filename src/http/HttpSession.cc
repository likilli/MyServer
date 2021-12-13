/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */


#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <cstring>

#include "HttpSession.h"
#include "Event.h"
#include "Utils.h"


constexpr int kBufSize = 8192;
const char* kHeader = "HTTP/1.1 200 OK\r\n"
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
    DoRead();
}


void HttpSession::DoRead()
{
    char buf[kBufSize]{};
    ssize_t read_len = recv(socket_.GetSocket(), buf, kBufSize - 1, 0);
    if (read_len == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            StartRead(socket_.GetSocket(), [this](){ DoRead(); });
            return;
        }
    }

    // todo: use char array
    if (strstr(buf, "\r\n\r\n"))
        HttpUtils::ParseHttpHeaderFrom(buf, read_len, http_header_);

    if (recv_buffer_.find("\r\n\r\n") != std::string::npos)
    {
        //http_header_ = Utils::ParseHttpHeaderFrom(recv_buffer_);
        Utils::Log(0, "Http Header: ");
        StopRead(socket_.GetSocket());
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
    shutdown(socket_.GetSocket(), SHUT_RDWR);
    ::close(socket_.GetSocket());
}
