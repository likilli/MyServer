/*
 * HttpSession.hpp
 * Written by likilli on 2020-06-21 14:58
 *
 */


#pragma once

#include <map>
#include <string>

#include "Event.hpp"


class HttpSession
{
public:

    HttpSession();
    ~HttpSession();

    HttpSession(HttpSession&&) = delete;
    HttpSession(const HttpSession&) = delete;
    HttpSession& operator=(HttpSession &&) = delete;
    HttpSession& operator=(const HttpSession&) = delete;

private:

    std::map<std::string, std::string> http_headers_{}

};

