#pragma once


#include <cassert>

#include "Event.hpp"


void AddEvent(int fd, EventType event_type, CallBack cb);
void DelEvent(int fd, EventType event_type);





