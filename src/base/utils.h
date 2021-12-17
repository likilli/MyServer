#pragma once


#include <map>
#include <string>


class StringUtils
{
public:
    static bool StartWith(const char* src, const char* needle);
};


class HttpUtils
{
public:
    static bool ParseHttpHeaderFrom(const char* buf, ssize_t buf_len, std::map<std::string, std::string>& http_header);
};


class Utils
{
public:
    static void Log(int level, const std::string& info);
};