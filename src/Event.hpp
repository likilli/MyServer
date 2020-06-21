#pragma once

#include <sys/select.h>
#include <vector>

#include "Core.hpp"


class Event
{

public:

    void Start(event &e);
    void Stop(event &e);

public:

    Event() = default;
    ~Event() = default;

    Event(const Event&) = delete;
    Event(Event &&) = delete;
    Event& operator=(const Event&) = delete;
    Event& operator=(Event&&) = delete;

private:

    int fd_max_ = 0;

    std::vector<event> ev_vec_{};

    fd_set rfds_{};
    fd_set wfds_{};
};