#pragma once


#include <map>
#include <string>


class Utils
{
public:
    static void Log(int level, const std::string& info);
    static void Log(int level, const std::map<std::string, std::string> &v);

    static void ParseHttpHeaderFrom(const char* buf, ssize_t buf_len, std::map<std::string, std::string>& http_header);
};