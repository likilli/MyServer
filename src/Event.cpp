#include "Event.hpp"

#include <algorithm>

/**
 *
 * @param e
 */
void Event::Start(event &e)
{
    const int &fd = e.fd_;

    fd_max_ = e.fd_ > fd_max_ ? e.fd_ + 1 : fd_max_;

    if (e.event_type_ == EVENT_READ)
        FD_SET(fd, &rfds_);
    else
        FD_SET(fd, &wfds_);


    struct timeval timeout{};
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;

    while (true)
    {
        int select_rc = select(fd_max_, &rfds_, &wfds_, nullptr, &timeout);
        if (select_rc == -1)
            break;

        for (const auto &t : ev_vec_)
        {
            if (t.event_type_ == EVENT_READ && FD_ISSET(e.fd_, &rfds_))
            {
                e.onCallBack_;
            }
            if (t.event_type_ == EVENT_WRITE && FD_ISSET(e.fd_, &wfds_))
            {
                e.onCallBack_;
            }
        }

        for_each(ev_vec_.begin(), ev_vec_.end(), [&](const event &t){
            if (t.event_type_ == EVENT_READ)
                FD_SET(t.fd_, &rfds_);
            else
                FD_SET(t.fd_, &wfds_);
        });

    }

}

/**
 *
 * @param e
 */
void Event::Stop(event &e)
{
    const int &fd = e.fd_;

    if (e.event_type_ == EVENT_READ)
        FD_CLR(fd, &rfds_);
    else
        FD_CLR(fd, &wfds_);
}