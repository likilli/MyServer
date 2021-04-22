#pragma once


#include <functional>
#include "Core.hpp"


using CallBack = std::function<void()>;

struct Event
{
    int          fd_ = 0;
    EventType    event_type_{};
    CallBack     callback_ = nullptr;

    bool operator==(const Event &e) const
    {
        return e.fd_ == fd_ && e.event_type_ == event_type_;
    }
};


void EventInit(CallBack callback);
void EventStart(int fd, EventType event_type, CallBack call_back);
void EventStop(int fd, EventType event_type);