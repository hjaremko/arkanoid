#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "event_handler_imp.hpp"
#include "event.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include "windows_event_handler.hpp"
#else
    #include "curses_event_handler.hpp"
#endif

class event_handler
{
public:
    event_handler()
    {
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            m_handler = new windows_event_handler;
        #else
            m_handler = new curses_event_handler;
        #endif
    }

    ~event_handler()
    {
        delete m_handler;
    }

    bool get_event( event& t_event )
    {
        return m_handler->dev_get_event( t_event );
    }

private:
    event_handler_imp* m_handler;
};

#endif
