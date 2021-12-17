#pragma once


#include <string>
#include <functional>


#if !defined(__WIN32)
#define Socket int
#endif


constexpr int READ = 0;
constexpr int WRITE = 1;


class PosixSocket
{
public:
    using OnReadCallback = std::function<void()>;
    using OnSendCallback = std::function<void()>;

public:
    PosixSocket();
    explicit PosixSocket(Socket socket);
    ~PosixSocket();

public:
    void StartRead(OnReadCallback cb) const;
    void StopRead();
    void StartSend(OnSendCallback) const;
    void StopSend();

    void SetSendData(const std::string& data);
    void SetSendData(const char* data, size_t data_size);

    Socket GetSocket() const { return socket_; }
    std::string GetRecvData() const;

private:
    Socket socket_{};

    std::size_t sent_len_{};
    std::string send_buffer_{};
    std::string recv_buffer_{};
};