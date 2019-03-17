#ifndef EVENTHANDLERIMP_H
#define EVENTHANDLERIMP_H

#include "event.hpp"

class event_handler_imp
{
public:
    event_handler_imp() = default;
    virtual ~event_handler_imp() = default;
    virtual bool dev_get_event( event& ) = 0;
};

#endif
