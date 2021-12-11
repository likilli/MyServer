#include "EventImpl.h"


// condition implementation
#if defined(USE_SELECT)


#include <sys/select.h>
#include <vector>
#include <algorithm>


fd_set rfds{};
fd_set wfds{};
int  fd_max{-1};

std::vector<Event> events{};
static bool isLoopRunning{false};


static void EventLoopRun();


/**
 *
 * @param fd
 * @param event_type
 * @param cb
 */
void AddEvent(int fd, int event_type, Callback cb)
{
    assert(cb != nullptr);

    Event e{fd, event_type, std::move(cb)};
    fd_max = fd >= fd_max ? fd + 1 : fd_max;

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter == events.end())
        events.emplace_back(e);

    FD_CLR(fd, &rfds);
    FD_CLR(fd, &wfds);

    if (event_type == READ)
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
void DelEvent(int fd, int event_type)
{
    Event e{fd, event_type, nullptr};

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter != events.end())
        events.erase(iter);
}


static void EventLoopRun()
{
    isLoopRunning = true;
    while (true)
    {
        struct timeval timeout{0, 1000};

        FD_ZERO(&rfds);
        FD_ZERO(&wfds);

        for_each(events.begin(), events.end(), [&](const Event &t)
        {
            if (t.event_type == READ)
                FD_SET(t.fd, &rfds);
            else
                FD_SET(t.fd, &wfds);
        });


        int select_rc = select(fd_max, &rfds, &wfds, nullptr, &timeout);
        if (select_rc == -1)
            break;

        for (const auto &t : events)
        {
            if (FD_ISSET(t.fd, &rfds) || FD_ISSET(t.fd, &wfds))
            {
                t.callback_();
            }
        }
    }
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