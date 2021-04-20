#pragma once


#include <functional>
#include "Core.hpp"


using CallBack = std::function<void()>;


void EventStart(int fd, EventType event_type, CallBack call_back);
void EventStop(int fd, EventType event_type);
void EventLoopRun();