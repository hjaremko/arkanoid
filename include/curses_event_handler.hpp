#ifndef CURSESEVENTHANDLERIMP_H
#define CURSESEVENTHANDLERIMP_H

#include "curses.h"
#include "event.hpp"
#include "event_handler_imp.hpp"

class curses_event_handler : public event_handler_imp
{
public:
    curses_event_handler()
    {
        keypad( stdscr, TRUE );
        mousemask( ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL );
        // printf( "\033[?1003h\n" );
    }

    ~curses_event_handler() override = default;

    bool dev_get_event( event& t_event ) override
    {
        int c = wgetch( stdscr );
        MEVENT event;

        switch ( c )
        {
        case KEY_MOUSE:
        {
#if defined( WIN32 )
            if ( nc_getmouse( &event ) == OK )
#else
            if ( getmouse( &event ) == OK )
#endif
            {
                mvprintw( 1, 1, "%d", event.bstate );
                std::this_thread::sleep_for( seconds( 10 ) );

                if ( event.bstate & BUTTON1_CLICKED )
                {
                    t_event.type = event::type::mouse_pressed;
                    t_event.mouse_button.button = mouse::button::button1;
                }
                else if ( event.bstate & BUTTON3_CLICKED )
                {
                    t_event.type = event::type::mouse_pressed;
                    t_event.mouse_button.button = mouse::button::button3;
                }
                else
                {
                    t_event.type = event::type::mouse_moved;
                    t_event.mouse_move.y = event.y;
                    t_event.mouse_move.x = event.x;
                }
            }

            break;
        }
        case 'q':
            t_event.type = event::type::key_pressed;
            t_event.key.code = keyboard::key::Q;

            break;
        default:
            break;
        }

        return true;
    }
};

#endif
