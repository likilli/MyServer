#include "Socket.hpp"
#include <unistd.h>
#include <sys/socket.h>


Socket::Socket()
{
    socket_ = socket(PF_INET, SOCK_STREAM, 0);
}


Socket::~Socket()
{
    if (socket_ != -1)
    {
        shutdown(socket_, SHUT_RDWR);
        ::close(socket_);
        socket_ = -1;
    }
}


void Socket::SetSendData(const char *data, size_t data_size)
{
    send_buffer_.append(data, data_size);
}


void Socket::SetSendData(const std::string& data)
{
    send_buffer_.append(data);
}


std::string Socket::GetRecvData() const
{
    return recv_buffer_;
}