#pragma once


#include <cassert>
#include <Core.hpp>
#include <functional>


using CallBack = std::function<void()>;


struct Event
{
    int fd;
    EventType type;
    CallBack  cb;

    bool operator==(const Event& e) const
    {
        return e.fd == fd && e.type == type;
    }
};


void AddEvent(int fd, EventType event_type, CallBack cb);
void DelEvent(int fd, EventType event_type);





