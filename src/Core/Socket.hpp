#pragma once


#include <string>


#ifndef __WIN32
#define socket_type int
#else
#define socket_type Socket
#endif


class Socket
{
public:
    Socket();
    ~Socket();

public:
    void SetSendData(const char* data, size_t data_size);
    void SetSendData(const std::string& data);
    std::string GetRecvData() const;

private:

   socket_type socket_{};

   std::string send_buffer_{};
   std::string recv_buffer_{};
};