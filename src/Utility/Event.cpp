#include "Event.hpp"

#include <sys/select.h>
#include <vector>
#include <algorithm>

#include "EventImpl.hpp"


/**
 *
 * @param cb
 */
void EventInit(CallBack)
{
    return;
}

/**
 *
 * @param fd
 * @param event_type
 * @param call_back
 * @param data
 */
void EventStart(int fd, int event_type, CallBack call_back)
{
    AddEvent(fd, event_type, std::move(call_back));
}

/**
 *
 * @param fd
 * @param event_type
 */
void EventStop(int fd, int event_type)
{
    DelEvent(fd, event_type);
}