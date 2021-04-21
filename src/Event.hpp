#pragma once


#include <functional>
#include "Core.hpp"
#include "EventImpl.hpp"




void EventInit(CallBack callback);
void EventStart(int fd, EventType event_type, CallBack call_back);
void EventStop(int fd, EventType event_type);
void EventLoopRun();