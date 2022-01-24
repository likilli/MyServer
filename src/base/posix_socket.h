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
    using OnDoneCallback = std::function<void()>;
    using OnErrorCallback = std::function<void(int)>;

public:
    PosixSocket();
    explicit PosixSocket(Socket socket);
    ~PosixSocket();

public:
    void StartRead(OnReadCallback cb) const;
    void StopRead();

    void SetSendData(const std::string& data);
    void SetSendData(const char* data, size_t data_size);

    void SetOnDoneCallback(OnDoneCallback cb);
    void SetOnErrorCallback(OnErrorCallback cb);

    bool Working() const { return working_; }
    Socket GetSocket() const { return socket_; }

    std::string GetRecvData() const;
    void Close();

private:
    void DoSend();

private:
    Socket socket_{};

    bool working_{true};

    std::size_t sent_len_{};
    std::size_t recv_len_{};
    std::string send_buffer_{};
    std::string recv_buffer_{};

    OnDoneCallback on_done_{};
    OnErrorCallback on_error_{};
};
