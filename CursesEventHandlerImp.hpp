#ifndef CURSESEVENTHANDLERIMP_H
#define CURSESEVENTHANDLERIMP_H

#include "EventHandlerImp.hpp"
#include "Event.hpp"

class CursesEventHandlerImp : public EventHandlerImp
{
    public:
        CursesEventHandlerImp()
        {
            keypad( stdscr, TRUE );
            mousemask( ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL );
        }

        ~CursesEventHandlerImp() {}

        Event* devGetEvent()
        {
            int c = wgetch( stdscr );
            switch( c )
            {
                MEVENT event;
                case KEY_MOUSE:
                {

                    if ( nc_getmouse( &event ) == OK )
                    {
                        if ( event.bstate & BUTTON1_CLICKED )
                        {
                            return new Event( Event::Button::Mouse1, event.y, event.x );
                        }

                        if ( event.bstate & BUTTON3_CLICKED )
                        {
                            return new Event( Event::Button::Mouse3, event.y, event.x );
                        }
                    }

                    return new Event( Event::Button::Other, event.y, event.x );
                }
                case 'q':
                    return new Event( Event::Button::Q, event.y, event.x );
                    break;
                default:
                    return new Event( Event::Button::Other, event.y, event.x );

            }
        }

    private:
};

#endif
