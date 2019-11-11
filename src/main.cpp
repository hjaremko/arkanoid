#include "ball.hpp"
#include "ball_state.hpp"
#include "event_handler.hpp"
#include "map.hpp"
#include "map_drawing.hpp"

#include <cstdio>
#include <curses.h>
#include <mutex>
#include <random>

std::mutex m;
std::mt19937 engine( static_cast<unsigned int>( time( nullptr ) ) );

int random( int min, int max )
{
    return std::uniform_int_distribution<int> { min, max }( engine );
}

void init_color()
{
    init_pair( 1, COLOR_RED, COLOR_BLACK );
    init_pair( 2, COLOR_GREEN, COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW, COLOR_BLACK );
    init_pair( 4, COLOR_BLUE, COLOR_BLACK );
    init_pair( 5, COLOR_MAGENTA, COLOR_BLACK );
    init_pair( 6, COLOR_CYAN, COLOR_BLACK );
    init_pair( 7, COLOR_WHITE, COLOR_BLACK );
}

int main()
{
    constexpr auto MIN_WIDTH { 120 };
    constexpr auto MIN_HEIGHT { 50 };

    initscr();
    noecho();
    curs_set( 0 );

    if ( has_colors() == FALSE )
    {
        endwin();
        printf( "Your terminal does not support color\n" );

        return 1;
    }

    start_color();
    init_color();

    if ( !map::instance()->read_current_level() )
    {
        map::instance()->init_paddle();
        map::instance()->init_blocks();
    }

    if ( getmaxx( stdscr ) < MIN_WIDTH || getmaxy( stdscr ) < MIN_HEIGHT )
    {
        map::instance()->set_message( "Please resize your terminal to at least 120 x 50 characters "
                                      "before playing the game." );
    }

    map_drawing map_drawing;
    std::thread drawing_thread( map_drawing );
    drawing_thread.detach();

    event_handler event_handler;
    event event;

    while ( true )
    {
        event_handler.get_event( event );

        switch ( event.type )
        {
        case event::type::key_pressed:
        {
            if ( event.key.code == keyboard::key::Q )
            {
                endwin();
                fflush( stdout );
                return 0;
            }

            break;
        }

        case event::type::mouse_pressed:
        {
            map::instance()->set_message( "" );

            switch ( event.mouse_button.button )
            {
            case mouse::button::button1:
            {
                map::instance()->get_paddle()->shoot();

                break;
            }

            case mouse::button::button3:
            {
                map::instance()->get_paddle()->secondary_action();

                break;
            }

            default:
                break;
            }

            break;
        }

        case event::type::mouse_moved:
        {
            point new_position( map::instance()->get_paddle()->gety(),
                                event.mouse_move.x -
                                    ( map::instance()->get_paddle()->width() / 2 ) );
            map::instance()->get_paddle()->set_position( new_position );

            break;
        }

        default:
            break;
        }
    }
}
