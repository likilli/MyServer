/*
 * HttpSession.hpp
 * Written by likilli on 2020-06-21 14:58
 *
 */


#pragma once


#include <map>
#include <string>

#include "Socket.h"


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
    explicit HttpSession(int fd);
    ~HttpSession();

    HttpSession(HttpSession&&) = delete;
    HttpSession(const HttpSession&) = delete;
    HttpSession& operator=(HttpSession &&) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

public:
    void Close();
    void Read();
    void Send();

private:
    void DoRead();
    void OnSend();

private:
    Socket socket_{};

    std::string recv_buffer_{};
    std::string send_buffer_{};

    Status status_{Status::kInit};
    std::map<std::string, std::string> http_header_{};
};

