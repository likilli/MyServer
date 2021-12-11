#pragma once


#include <cassert>

#include "Event.h"


void AddEvent(int fd, int event_type, CallBack cb);
void DelEvent(int fd, int event_type);