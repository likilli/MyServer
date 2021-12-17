#include "utils.h"

#include <cstring>
#include <iostream>


void Utils::Log(int level, const std::string& info)
{
    std::cout << "[LOG]: " << info << std::endl;
}


bool StringUtils::StartWith(const char* src, const char* needle)
{
    if (src == nullptr || needle == nullptr)
        return false;

    if (strlen(src) < strlen(needle))
        return false;

    bool ok = true;
    for (size_t i = 0; i < strlen(needle); i++)
    {
        if (src[i] != needle[i])
        {
            ok = false;
            break;
        }
    }
    return ok;
}


bool HttpUtils::ParseHttpHeaderFrom(const char* buf, ssize_t buf_len, std::map<std::string, std::string>& http_header)
{
    if (!strstr(buf, "\r\n\r\n"))
        return false;

    char http_code[10]{};
    char http_path[500]{};
    char http_method[10]{};
    char http_version[10]{};
    char http_phase[100]{}; // TODO: use correct word

    // Request Header
    if (StringUtils::StartWith(buf, "GET"))
    {
        sscanf(buf, "%s %s HTTP/%s", http_method, http_path, http_version);
        http_header.insert({"http_method", std::string(http_method)});
        http_header.insert({"http_path", std::string(http_path)});
        http_header.insert({"http_version", std::string(http_version)});
    }

    // Response Header
    if (StringUtils::StartWith(buf, "HTTP"))
    {
        sscanf(buf, "HTTP/%s %s %s", http_version, http_code, http_phase);
        http_header.insert({"http_version", std::string(http_version)});
        http_header.insert({"http_code", std::string(http_code)});
        http_header.insert({"http_phase", std::string(http_phase)});
    }

    // get first \r address
    ssize_t addr = 0;
    for (ssize_t i = 0; i < buf_len; i++)
    {
        if (buf[i] == '\r')
        {
            addr = i;
            break;
        }
    }
    addr += 2;

    // get http header end address
    ssize_t end_addr = 0;
    for (ssize_t i = addr; i < buf_len - 1; i++)
    {
        if (buf[i] == '\n' && buf[i+1] == '\r')
        {
            end_addr = i;
            break;
        }
    }

    // parse extra item
    bool isValue = false;
    bool first = false;
    std::string key{};
    std::string value{};

    for (ssize_t i = addr; i < end_addr; i++)
    {

        if (!first && buf[i] == ':')
        {
            isValue = true;
            first = true;
            i+=1;
            continue;
        }
        if (buf[i] == '\r')
        {
            http_header.insert({key, value});
            key.clear();
            value.clear();
            isValue = false;
            first = false;
            continue;
        }
        if (buf[i] == '\n') continue;

        if (!isValue) key += buf[i];
        if (isValue) value += buf[i];
    }

    return true;
}