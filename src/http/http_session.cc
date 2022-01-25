/*
 * HttpSession.cpp
 * Written by likai on 2020-06-21 14:59
 *
 */


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
    Close();
}


void HttpSession::Start()
{
    DoRead();
}


void HttpSession::Send()
{
    socket_.SetSendData(kHeader, strlen(kHeader));
    socket_.SetOnDoneCallback([&](){ OnSendDone(); });
    socket_.SetOnErrorCallback([&](int err_no){ OnSendError(err_no); });
    socket_.StartSend();
}


void HttpSession::Close()
{
    if (!http_header_.empty())
        http_header_.clear();

    if (!recv_buffer_.empty())
        recv_buffer_.clear();

    socket_.Close();
}


void HttpSession::DoRead()
{
    char buf[kBufSize]{};
    ssize_t recv_len = recv(socket_.GetSocket(), buf, kBufSize - 1, 0);
    if (recv_len == -1)
    {
#ifdef __APPLE__
        if (errno == EAGAIN)
#elif __linux__
        if (errno == EAGAIN || errno == EWOULDBLOCK)
#endif
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

    http_header_ = HttpUtils::ParseHttpHeaderFrom(buf, recv_len);
    if (!http_header_.empty())
    {
        socket_.StopRead();
        std::cout << "[LOG]: Request Header: " << std::endl;
        for (const auto& t : http_header_)
            std::cout << t.first << " : " << t.second << std::endl;

        status_ = Status::kSendResponseHeader;
        Send();
    }

}


void HttpSession::OnSendDone()
{
    socket_.StopSend();
    Close();
}


void HttpSession::OnSendError(int err_no)
{
    std::cerr << "[ERROR]: " << __FUNCTION__  << ", errno: " << err_no << " : " << strerror(err_no) << std::endl;
    Close();
}
