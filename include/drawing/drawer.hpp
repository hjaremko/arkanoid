#ifndef ARKANOID_DRAWER_HPP
#define ARKANOID_DRAWER_HPP

#include "map.hpp"

#include <curses.h>
#include <iostream>

namespace arkanoid
{
class drawer
{
public:
    drawer()
    {
        initscr();
        noecho();
        curs_set( 0 );

        if ( !has_colors() )
        {
            std::cerr << "Your terminal does not support color\n";
            throw;
        }

        start_color();
        init_color();
    }

    drawer( const drawer& ) = default;
    drawer( drawer&& ) = default;
    auto operator=( const drawer& ) -> drawer& = default;
    auto operator=( drawer && ) -> drawer& = default;

    virtual ~drawer()
    {
        endwin();
    }

//    void update()
//    {
//    }

    static void draw( const map& to_draw )
    {
        clear();
        to_draw.draw();

        if ( getmaxx( stdscr ) < MIN_WIDTH || getmaxy( stdscr ) < MIN_HEIGHT )
        {
            mvprintw(
                2,
                5,
                "Please resize your terminal to at least 120 x 50 characters "
                "before playing the game." );
        }

        refresh();
    }

private:
    static void init_color()
    {
        init_pair( 1, COLOR_RED, COLOR_BLACK );
        init_pair( 2, COLOR_GREEN, COLOR_BLACK );
        init_pair( 3, COLOR_YELLOW, COLOR_BLACK );
        init_pair( 4, COLOR_BLUE, COLOR_BLACK );
        init_pair( 5, COLOR_MAGENTA, COLOR_BLACK );
        init_pair( 6, COLOR_CYAN, COLOR_BLACK );
        init_pair( 7, COLOR_WHITE, COLOR_BLACK );
    }

    static constexpr auto MIN_WIDTH { 120 };
    static constexpr auto MIN_HEIGHT { 50 };
};
} // namespace arkanoid

#endif // ARKANOID_DRAWER_HPP
