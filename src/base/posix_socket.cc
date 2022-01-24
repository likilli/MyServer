#include "posix_socket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <utility>
#include <fcntl.h>

#include "event.h"


constexpr uint32_t kBufSize = 8192;


PosixSocket::PosixSocket()
{
    socket_ = socket(PF_INET, SOCK_STREAM, 0);
    fcntl(socket_, F_SETFL, fcntl(socket_, F_GETFL) | O_NONBLOCK);
}


PosixSocket::PosixSocket(Socket fd) : socket_(fd)
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


void PosixSocket::StartRead(OnReadCallback cb) const
{
    EventAdd(socket_, READ, std::move(cb));
}


void PosixSocket::StopRead()
{
    EventDel(socket_, READ);
}


void PosixSocket::StartSend(OnSendCallback cb) const
{
    EventAdd(socket_, WRITE, std::move(cb));
}


void PosixSocket::StopSend()
{
    EventDel(socket_, WRITE);
}


void PosixSocket::SetSendData(const std::string& data)
{
    send_buffer_.append(data);
}


void PosixSocket::SetSendData(const char *data, size_t data_size)
{
    send_buffer_.append(data, data_size);
}


std::string PosixSocket::GetRecvData() const
{
    return recv_buffer_;
}
