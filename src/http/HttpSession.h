/*
 * HttpSession.hpp
 * Written by likilli on 2020-06-21 14:58
 *
 */


#pragma once


#include <map>
#include <string>

#include "posix_socket.h"


enum class Status : int
{
    kInit               = 0,
    kRecvRequest        = 1,
    kSendResponseHeader = 2,
    kSendResponseData   = 3
};


class HttpSession
{
public:
    explicit HttpSession(Socket socket);
    ~HttpSession();

    HttpSession(HttpSession&&) = delete;
    HttpSession(const HttpSession&) = delete;
    HttpSession& operator=(HttpSession &&) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

public:
    void Read();
    void Send();
    void Close();

private:
    void DoRead();
    void DoSend();

private:
    PosixSocket socket_{};

    std::string recv_buffer_{};
    std::string send_buffer_{};

    Status status_{Status::kInit};
    std::map<std::string, std::string> http_header_{};
};

