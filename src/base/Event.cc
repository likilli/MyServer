#include "Event.h"
#include "EventImpl.h"


/**
 *
 * @param cb
 */
void EventInit(Callback)
{
}


void StartRead(int socket, Callback cb)
{
    AddEvent(socket, READ, std::move(cb));
}


void StopRead(int socket)
{
    DelEvent(socket, READ);
}


void StartWrite(int socket, Callback cb)
{
    AddEvent(socket, WRITE, std::move(cb));
}


void StopWrite(int socket)
{
    DelEvent(socket, WRITE);
}