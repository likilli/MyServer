#pragma once


#include <string>
#include <functional>


#if !defined(__WIN32)
#define Socket int
#endif


constexpr int READ  = 0;
constexpr int WRITE = 1;


class PosixSocket
{
public:
    using OnReadCallback = std::function<void()>;
    using OnDataCallback = std::function<void(std::string& data)>;
    using OnDoneCallback = std::function<void()>;
    using OnErrorCallback = std::function<void(int)>;

public:
    PosixSocket();
    explicit PosixSocket(Socket socket);
    ~PosixSocket();

public:
    void StartRead();
    void StopRead() const;
    void SetOnReadCallback(OnReadCallback cb);
    void SetOnDataCallback(OnDataCallback cb);

    void StartSend();
    void StopSend() const;
    void SetSendData(const std::string& data);
    void SetSendData(const char* data, size_t data_size);

    void SetOnDoneCallback(OnDoneCallback cb);
    void SetOnErrorCallback(OnErrorCallback cb);

    void Close();

    Socket GetSocket() const { return socket_; }

private:
    void DoSend();
    void DoRead();

private:
    Socket socket_{};

    std::size_t sent_len_{};
    std::size_t recv_len_{};
    std::string send_buffer_{};
    std::string recv_buffer_{};

    OnReadCallback on_read_{};
    OnDataCallback on_data_{};

    OnDoneCallback on_done_{};
    OnErrorCallback on_error_{};
};
