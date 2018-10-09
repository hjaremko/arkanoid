#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventHandlerImp.hpp"
#include "CursesEventHandlerImp.hpp"
#include "Event.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include "WindowsEventHandlerImp.hpp"
#endif

class EventHandler
{
    public:
        EventHandler()
        {
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                m_handler = new WindowsEventHandlerImp;
            #else
                m_handler = new CursesEventHandlerImp;
            #endif
        }
        ~EventHandler() {}

        Event* getEvent()
        {
            return m_handler->devGetEvent();
        }

    private:
        EventHandlerImp* m_handler;
};

#endif
