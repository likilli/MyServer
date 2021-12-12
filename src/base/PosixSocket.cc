#include "PosixSocket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "Event.h"


PosixSocket::PosixSocket()
{
    socket_ = socket(PF_INET, SOCK_STREAM, 0);
    fcntl(socket_, F_SETFL, fcntl(socket_, F_GETFL) | O_NONBLOCK);
}


PosixSocket::PosixSocket(int fd) : socket_(fd)
{
    fcntl(socket_, F_SETFL, fcntl(socket_, F_GETFL) | O_NONBLOCK);
}


PosixSocket::~PosixSocket()
{
    if (socket_ != -1)
    {
        shutdown(socket_, SHUT_RDWR);
        ::close(socket_);
        socket_ = -1;
    }
}


void PosixSocket::SetSendData(const char *data, size_t data_size)
{
    send_buffer_.append(data, data_size);
}


void PosixSocket::SetSendData(const std::string& data)
{
    send_buffer_.append(data);
}


std::string PosixSocket::GetRecvData() const
{
    return recv_buffer_;
}


void PosixSocket::Send()
{
    OnSend();
}


void PosixSocket::OnSend() {
    uint64_t send_len = ::send(socket_, send_buffer_.c_str() + sent_len_, send_buffer_.length() - sent_len_, 0);
    if (send_len >= 0)
        sent_len_ += send_len;
    else
        StartWrite(socket_, [this](){ OnSend(); });
}