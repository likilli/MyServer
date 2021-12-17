#include "event.h"


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


/**
 *
 * @param socket
 * @param event_type
 * @param cb
 */
void EventAdd(int socket, int event_type, Callback cb)
{
    assert(cb != nullptr);

    Event e{socket, event_type, std::move(cb)};
    fd_max = socket >= fd_max ? socket + 1 : fd_max;

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter == events.end())
        events.emplace_back(e);
}


/**
 *
 * @param socket
 * @param event_type
 */
void EventDel(int socket, int event_type)
{
    Event e{socket, event_type, nullptr};

    auto iter = std::find(events.begin(), events.end(), e);
    if (iter != events.end())
        events.erase(iter);
}


void EventLoopRun()
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
                FD_SET(t.socket, &rfds);
            else
                FD_SET(t.socket, &wfds);
        });


        int select_rc = select(fd_max, &rfds, &wfds, nullptr, &timeout);
        if (select_rc == -1)
            break;

        for (const auto &t : events)
        {
            if (FD_ISSET(t.socket, &rfds) || FD_ISSET(t.socket, &wfds))
            {
                t.callback_();
            }
        }
    }
}


int GetEventQuantity()
{
    return static_cast<int>(events.size());
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