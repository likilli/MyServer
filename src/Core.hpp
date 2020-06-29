#pragma once

#include <functional>

constexpr int EVENT_READ  = 0;
constexpr int EVENT_WRITE = 1;

struct event
{
    int                    fd_{};
    int                    event_type_{};
    void                  *data_ = nullptr;
    std::function<void(void *)>  onCallBack_ = nullptr;

    bool operator== (const event &var) const
    {
        return var.fd_ == fd_ && var.event_type_ == event_type_;
    }
};