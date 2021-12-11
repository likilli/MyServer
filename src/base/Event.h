#pragma once


#include <functional>


constexpr int READ = 0;
constexpr int WRITE = 1;
using Callback = std::function<void()>;


struct Event
{
    int          fd{-1};
    int          event_type{};
    Callback     callback_{nullptr};

    bool operator==(const Event &e) const
    {
        return e.fd == fd && e.event_type == event_type;
    }
};


void EventInit(Callback callback);

void StartRead(int fd, Callback cb);
void StopRead(int fd);
void StartWrite(int fd, Callback cb);
void StopWrite(int fd);