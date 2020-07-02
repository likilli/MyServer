#pragma once

#include "Core.hpp"

using CallBack = void (*)(void *);

void EventStart(int fd, EventType event_type, CallBack call_back, void *data);

void EventStop(int fd, EventType event_type);