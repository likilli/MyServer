#pragma once


#include <map>
#include <string>


class Utils
{
public:
    static void Log(int level, const std::string& info);
    static void Log(int level, const std::map<std::string, std::string> &v);

    static std::map<std::string, std::string> ParseHttpHeaderFrom(std::string& buffer);
};