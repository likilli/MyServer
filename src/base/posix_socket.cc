#include "posix_socket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <utility>
#include <fcntl.h>

#include "event.h"


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
    Close();    // TODO: Charify here: DO NOT Call any function in destuctor (Effective C++);
}


void PosixSocket::Close()
{
    if (socket_ != -1)
    {
        shutdown(socket_, SHUT_RDWR);
        EventDel(socket_, READ);
        EventDel(socket_, WRITE);
        close(socket_);
        socket_ = -1;
        working_ = false;
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


void PosixSocket::SetSendData(const std::string& data)
{
    send_buffer_.append(data);
    EventAdd(socket_, WRITE, [&](){ DoSend(); });
}


void PosixSocket::SetSendData(const char *data, size_t data_size)
{
    send_buffer_.append(data, data_size);
    EventAdd(socket_, WRITE, [&](){ DoSend(); });
}


void PosixSocket::SetOnDoneCallback(OnDoneCallback cb)
{
    assert(cb != nullptr);
    on_done_ = std::move(cb);
}


void PosixSocket::SetOnErrorCallback(OnErrorCallback cb)
{
    assert(cb != nullptr);
    on_error_ = std::move(cb);
}


std::string PosixSocket::GetRecvData() const
{
    return recv_buffer_;
}


void PosixSocket::DoSend()
{
    ssize_t send_len = send(socket_, send_buffer_.c_str() + sent_len_, send_buffer_.length(), 0);
    if (send_len == -1)
    {
#ifdef __APPLE__
        if (errno == EAGAIN)
#elif __linux__
            if (errno == EAGAIN || errno == EWOULDBLOCK)
#endif
            return;
        else
            on_error_(errno);
    }

    sent_len_ += send_len;
    if (sent_len_ == send_buffer_.length())     //  TODO: Optimize here when send buffer is very large (huge memory use)
    {
        EventDel(socket_, WRITE);
        on_done_();
    }
}
