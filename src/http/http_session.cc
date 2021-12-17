/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */


#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <cstring>

#include <iostream>
#include "http_session.h"
#include "utils.h"


constexpr int kBufSize = 8192;
const char* kHeader = "HTTP/1.1 200 OK\r\n"
             "Connection: close\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: 85\r\n"
             "Server:elitk/Manjaro 20.0 - Lysia\r\n"
             "\r\n"
             "<!DOCTYPE html><html><head> Welcom, Kai</head><h1> aaa, elitk's Home page</h1></html>";


HttpSession::HttpSession(Socket socket) : socket_(socket)
{

}


HttpSession::~HttpSession()
{
    if (!http_header_.empty())
        http_header_.clear();
}


void HttpSession::Start()
{
    DoRead();
}


void HttpSession::Send()
{
    socket_.StartSend([this](){ DoSend(); });
}


void HttpSession::DoRead()
{
    char buf[kBufSize]{};
    ssize_t read_len = recv(socket_.GetSocket(), buf, kBufSize - 1, 0);
    if (read_len == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            socket_.StartRead([this](){ DoRead(); });
            return;
        }
        else
        {
            std::cerr << "[ERROR]: receive data error: " << errno << " : " << strerror(errno) << std::endl;
            Close();
        }
    }

    if (read_len == 0)
        socket_.StopRead();

    if (HttpUtils::ParseHttpHeaderFrom(buf, read_len, http_header_))
    {
        std::cout << "[LOG]: Request Header: " << std::endl;
        for (const auto& t : http_header_)
            std::cout << t.first << " : " << t.second << std::endl;

        status_ = Status::kSendResponseHeader;
        Send();
    }

}


void HttpSession::DoSend()
{

}


void HttpSession::Close()
{
    shutdown(socket_.GetSocket(), SHUT_RDWR);
    ::close(socket_.GetSocket());
}
