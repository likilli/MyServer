#pragma once


#include <functional>
#include "Types.h"


using CallBack = std::function<void()>;


struct Event
{
    int          fd{-1};
    int          event_type{};
    CallBack     callback_{nullptr};

    bool operator==(const Event &e) const
    {
        return e.fd == fd && e.event_type == event_type;
    }
};


void EventInit(CallBack callback);
void EventStart(int fd, int event_type, CallBack call_back);
void EventStop(int fd, int event_type);