#pragma once


#include <string>
#include <functional>


#if !defined(__WIN32)
#define Socket int
#endif


class PosixSocket
{
public:
    using OnErrorCallBack = std::function<void(int)>;

public:
    PosixSocket();
    explicit PosixSocket(int socket);
    ~PosixSocket();

public:
    void SetSendData(const char* data, size_t data_size);
    void SetSendData(const std::string& data);
    std::string GetRecvData() const;

    void Send();

    Socket GetSocket() const { return socket_; }

public:
    void SetOnErrorCallBack(OnErrorCallBack on_error) { on_error_ = std::move(on_error); }

private:
    void OnSend();

private:
    std::size_t sent_len_{};

private:

   Socket socket_{};

   std::string send_buffer_{};
   std::string recv_buffer_{};

   OnErrorCallBack on_error_{};
};