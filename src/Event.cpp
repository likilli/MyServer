#include "Event.hpp"

#include <sys/select.h>

#include <vector>
#include <algorithm>

using CallBack = void (*)(void *);

struct event
{
    int          fd_ = 0;
    EventType    event_type_{};
    CallBack     callback_ = nullptr;
    void        *data_     = nullptr;

    bool operator==(const event &e) const
    {
        return e.fd_ == fd_ && e.event_type_ == event_type_;
    }
};

int fd_max = 0;
fd_set rfds{};
fd_set wfds{};

static bool isLoopRunning = false;

std::vector<event> ev_vec{};

/**
 *
 * @param fd
 * @param event_type
 * @param call_back
 * @param data
 */
void EventStart(int fd, EventType event_type, CallBack call_back, void *data)
{

    fd_max = fd > fd_max ? fd + 1 : fd_max;
    event e{fd, event_type, call_back, data};

    auto iter = std::find(ev_vec.begin(), ev_vec.end(), e);
    if (iter == ev_vec.end())
        ev_vec.emplace_back(e);

    FD_CLR(fd, &rfds);
    FD_CLR(fd, &wfds);

    if (event_type == EventType::Read)
        FD_SET(fd, &rfds);
    else
        FD_SET(fd, &wfds);

    if (!isLoopRunning)
        EventLoopRun();
}

/**
 *
 * @param fd
 * @param event_type
 */
void EventStop(int fd, EventType event_type)
{
    event e{fd, event_type, nullptr, nullptr};
    auto iter = std::find(ev_vec.begin(), ev_vec.end(), e);
    if (iter != ev_vec.end())
        ev_vec.erase(iter);

    if (event_type == EventType::Read)
        FD_CLR(fd, &rfds);
    else
        FD_CLR(fd, &wfds);
}

void EventLoopRun()
{
    isLoopRunning = true;
    while (true)
    {
        struct timeval timeout{};
        timeout.tv_sec  = 0;
        timeout.tv_usec = 500;

        int select_rc = select(fd_max, &rfds, &wfds, nullptr, &timeout);
        if (select_rc == -1)
            break;

        for (const auto &t : ev_vec)
        {
            if (FD_ISSET(t.fd_, &rfds) || FD_ISSET(t.fd_, &wfds))
            {
                t.callback_(t.data_);
            }
        }

        for_each(ev_vec.begin(), ev_vec.end(), [&](const event &t){
            FD_CLR(t.fd_, &rfds);
            FD_CLR(t.fd_, &wfds);
        });

        for_each(ev_vec.begin(), ev_vec.end(), [&](const event &t){
            if (t.event_type_ == EventType::Read)
            {
                FD_SET(t.fd_, &rfds);
            }
            else
            {
                FD_SET(t.fd_, &wfds);
            }
        });
    }
}