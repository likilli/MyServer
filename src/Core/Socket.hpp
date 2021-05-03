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
    using OnErrorCallBack = std::function<void(int)>;

public:
    Socket();
    explicit Socket(int fd);
    ~Socket();

public:
    void SetSendData(const char* data, size_t data_size);
    void SetSendData(const std::string& data);
    std::string GetRecvData() const;

    void Send();

    socket_type GetFd() const { return socket_; }

public:
    void SetOnErrorCallBack(OnErrorCallBack on_error) { on_error_ = std::move(on_error); }

private:
    void OnSend();

private:
    std::size_t sent_len_{};

private:

   socket_type socket_{};

   std::string send_buffer_{};
   std::string recv_buffer_{};

   OnErrorCallBack on_error_{};
};