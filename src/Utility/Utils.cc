#include "Utils.h"

#include <iostream>


void Utils::Log(int level, const std::string& info)
{
    std::cout << "[LOG]: " << info << std::endl;
}


void Utils::ParseHttpHeaderFrom(const char* buf, ssize_t buf_len, std::map<std::string, std::string>& http_header)
{

    // todo:
    /*
    auto iter = buffer.find("\r\n\r\n");
    if (iter != std::string::npos)
    {
        std::string header(buffer, 0, iter + 2);
        buffer.erase(0, iter + 4);

        std::string item{};
        std::string key{};
        std::string value{};

        iter = header.find("\r\n");
        item.append(header, 0, iter);
        header.erase(0, iter + 2);
        // TODO: parse method, path, version

        bool ok = false;
        for (const auto& c : header)
        {
            if (c == ' ' || c == '\r') continue;
            if (c == ':')
            {
                ok = true;
                continue;
            }
            if (c == '\n')
            {
                ok = false;
                http_header.insert(std::pair<std::string, std::string>(key, value));
                key.clear();
                value.clear();
                continue;
            }

            if (ok) value += c;
            if (!ok) key += c;
        }
    }
    return http_header;
     */
}