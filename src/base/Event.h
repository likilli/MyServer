#pragma once


#include <functional>


constexpr int READ = 0;
constexpr int WRITE = 1;
using Callback = std::function<void()>;


struct Event
{
    int          socket{-1};
    int          event_type{};
    Callback     callback_{nullptr};

    bool operator==(const Event &e) const
    {
        return e.socket == socket && e.event_type == event_type;
    }
};


void EventInit(Callback callback);

void StartRead(int socket, Callback cb);
void StopRead(int socket);
void StartWrite(int socket, Callback cb);
void StopWrite(int socket);