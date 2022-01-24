#pragma once


#include <functional>
#include "posix_socket.h"


using Callback = std::function<void()>;


struct Event
{
    Socket       socket{-1};
    int          event_type{};
    Callback     callback_{nullptr};

    bool operator==(const Event &e) const
    {
        return e.socket == socket && e.event_type == event_type;
    }
};


void EventInit(Socket socket, int event_type, Callback callback);
void EventAdd(Socket socket, int event_type, Callback cb);
void EventDel(Socket socket, int event_type);
void EventLoopRun();
int GetEventQuantity();
