/*
 * HttpSession.hpp
 * Written by likilli on 2020-06-21 14:58
 *
 */


#pragma once

#include <map>
#include <string>


#include "Event.hpp"

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

    int getFd() const;

    void Close() const;
    static void OnRead(void *data);
    static void OnWrite(void *data);

public:

    explicit HttpSession(int fd);
    ~HttpSession();

    HttpSession(HttpSession&&) = delete;
    HttpSession(const HttpSession&) = delete;
    HttpSession& operator=(HttpSession &&) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

private:

    int     fd_ = -1;

    std::string buffer_{};
    ssize_t     sent_len_ = 0;

    Status status_{Status::kInit};
    std::map<std::string, std::string> http_header_{};
};

