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
            printf( "\033[?1003h\n" );
        }

        ~CursesEventHandlerImp() {}

        bool devGetEvent( Event& t_event )
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
                            t_event.type = Event::Type::MouseButtonPressed;
                            t_event.mouseButton.button = Mouse::Button::Button1;
                        }
                        else if ( event.bstate & BUTTON3_CLICKED )
                        {
                            t_event.type = Event::Type::MouseButtonPressed;
                            t_event.mouseButton.button = Mouse::Button::Button3;
                        }
                        else
                        {
                            t_event.type = Event::Type::MouseMoved;
                            t_event.mouseMove.y = event.y;
                            t_event.mouseMove.x = event.x;
                        }
                    }

                    break;
                }
                case 'q':
                    t_event.type = Event::Type::KeyPressed;
                    t_event.key.code = Keyboard::Key::Q;

                    break;
                default:
                    break;
            }

            return true;
        }

    private:
};

#endif
