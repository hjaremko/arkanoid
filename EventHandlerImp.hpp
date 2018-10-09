#ifndef EVENTHANDLERIMP_H
#define EVENTHANDLERIMP_H

#include "Event.hpp"

class EventHandlerImp
{
    public:
        EventHandlerImp() {}
        virtual ~EventHandlerImp() {}
        virtual Event* devGetEvent() = 0;
};

#endif
