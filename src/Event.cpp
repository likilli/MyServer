#include "Event.hpp"

#include <sys/select.h>

#include <vector>
#include <algorithm>

std::vector<event> ev_vec{};

int fd_max;
fd_set rfds{};
fd_set wfds{};

/**
 *
 * @param e
 */
void EventStart(const event &e)
{
    const int &fd = e.fd_;

    fd_max = e.fd_ > fd_max ? e.fd_ + 1 : fd_max;

    ev_vec.emplace_back(e);

    if (e.event_type_ == EVENT_READ)
        FD_SET(fd, &rfds);
    else
        FD_SET(fd, &wfds);


    struct timeval timeout{};
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;

    while (true)
    {
        int select_rc = select(fd_max, &rfds, &wfds, nullptr, &timeout);
        if (select_rc == -1)
            break;

        for (const auto &t : ev_vec)
        {
            if (t.event_type_ == EVENT_READ && FD_ISSET(e.fd_, &rfds))
            {
                e.onCallBack_;
            }
            if (t.event_type_ == EVENT_WRITE && FD_ISSET(e.fd_, &wfds))
            {
                e.onCallBack_;
            }
        }

        for_each(ev_vec.begin(), ev_vec.end(), [](const event &t){
            if (t.event_type_ == EVENT_READ)
                FD_SET(t.fd_, &rfds);
            else
                FD_SET(t.fd_, &wfds);
        });

    }

}

/**
 *
 * @param e
 */
void EventStop(const event &e)
{
    const int &fd = e.fd_;

    // use std::find replace for-loop
    for (auto iter = ev_vec.begin(); iter != ev_vec.end(); iter++)
    {
        if (*iter == e)
        {
            ev_vec.erase(iter);
            break;
        }
    }

    if (e.event_type_ == EVENT_READ)
        FD_CLR(fd, &rfds);
    else
        FD_CLR(fd, &wfds);
}