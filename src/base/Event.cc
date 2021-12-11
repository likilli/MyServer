#include "Event.h"
#include "EventImpl.h"


/**
 *
 * @param cb
 */
void EventInit(Callback)
{
}


void StartRead(int fd, Callback cb)
{
    AddEvent(fd, READ, std::move(cb));
}


void StopRead(int fd)
{
    DelEvent(fd, READ);
}


void StartWrite(int fd, Callback cb)
{
    AddEvent(fd, WRITE, std::move(cb));
}


void StopWrite(int fd)
{
    DelEvent(fd, WRITE);
}