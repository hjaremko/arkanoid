#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "event.hpp"
#include "event_handler_imp.hpp"
#include "game_manager.hpp"
#include "system.hpp"

#include <iostream>

#if defined( WIN32 ) || defined( _WIN32 ) ||                                   \
    defined( __WIN32 ) && !defined( __CYGWIN__ )
#include "windows_event_handler.hpp"
#else
#include "curses_event_handler.hpp"
#endif

#if defined( WIN32 ) || defined( _WIN32 ) ||                                   \
    defined( __WIN32 ) && !defined( __CYGWIN__ )
template <class HandlerPolicy = windows_event_handler>
#else
template <class HandlerPolicy = curses_event_handler>
#endif
struct event_handler : private HandlerPolicy
{
    explicit event_handler( arkanoid::system& system ) : system_( system )
    {
    }

    constexpr auto get_event( event& t_event ) -> bool
    {
        return HandlerPolicy::dev_get_event( t_event );
    }

    auto fetch_event() -> bool
    {
        event e;
        get_event( e );

        switch ( e.type )
        {
        case event::type::key_pressed:
        {
            if ( e.key.code == keyboard::key::Q )
            {
                return false;
            }
            break;
        }
        case event::type::mouse_pressed:
        {
            switch ( e.mouse_button.button )
            {
            case mouse::button::button1:
            {
                system_.push_task(
                    [=]( arkanoid::game_manager& gm ) { gm.shoot(); } );
                break;
            }
            case mouse::button::button3:
            {
                system_.push_task( [=]( arkanoid::game_manager& gm ) {
                    gm.secondary_action();
                } );
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
        case event::type::mouse_moved:
        {
            system_.push_task( [=]( arkanoid::game_manager& gm ) {
                gm.move_paddle( e.mouse_move.x );
            } );

            break;
        }
        default:
        {
            break;
        }
        }

        return true;
    }

private:
    arkanoid::system& system_;
};

#endif
