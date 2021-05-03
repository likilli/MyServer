#include "EventImpl.hpp"


// condition implementation
#if defined(USE_SELECT)


#include <sys/select.h>
#include <vector>
#include <algorithm>


std::vector<Event> events{};
static bool isLoopRunning = false;

int  fd_max{};
fd_set rfds{};
fd_set wfds{};


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

        for (const auto &t : events)
        {
            if (FD_ISSET(t.fd_, &rfds) || FD_ISSET(t.fd_, &wfds))
            {
                t.callback_();
            }
        }

        for_each(events.begin(), events.end(), [&](const Event &t)
        {
            FD_CLR(t.fd_, &rfds);
            FD_CLR(t.fd_, &wfds);
        });

        for_each(events.begin(), events.end(), [&](const Event &t)
        {
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


/**
 *
 * @param fd
 * @param event_type
 * @param cb
 */
void AddEvent(int fd, EventType event_type, CallBack cb)
{
    assert(cb != nullptr);

    Event e{fd, event_type, std::move(cb)};
    fd_max = fd > fd_max ? fd + 1 : fd_max;

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter == events.end())
        events.emplace_back(e);

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
void DelEvent(int fd, EventType event_type)
{
    Event e{fd, event_type, nullptr};

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter != events.end())
        events.erase(iter);
}


#elif defined(USE_EPOLL)

/*
 * todo : implement
 */

#elif defined(USE_LIBEVENT)

/*
 * todo: implement
 */

#endif