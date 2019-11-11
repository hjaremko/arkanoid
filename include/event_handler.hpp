#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "event.hpp"
#include "event_handler_imp.hpp"

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32 ) && !defined( __CYGWIN__ )
#include "windows_event_handler.hpp"
#else
#include "curses_event_handler.hpp"
#endif

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32 ) && !defined( __CYGWIN__ )
template <class HandlerPolicy = windows_event_handler>
#else
template <class HandlerPolicy = curses_event_handler>
#endif
struct event_handler : private HandlerPolicy
{
    constexpr bool get_event( event& t_event )
    {
        return HandlerPolicy::dev_get_event( t_event );
    }
};

#endif
