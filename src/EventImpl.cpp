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
}


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