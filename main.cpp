#include <vector>
#include <curses.h>

// #include "Entity.hpp"
#include "Block.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

void initColorPairs()
{
    init_pair( 1, COLOR_RED,     COLOR_BLACK );
    init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
    init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
    init_pair( 5, COLOR_MAGENTA, COLOR_BLACK );
    init_pair( 6, COLOR_CYAN,    COLOR_BLACK );
    init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
}

int main()
{
    initscr();
    noecho();
    curs_set( 0 );

    if( has_colors() == FALSE )
    {  
        endwin();
        printf( "Your terminal does not support color\n" );
        return 1;
    }

    start_color();
    initColorPairs();

    std::vector<Block> blocks{ static_cast<unsigned int>( getmaxx( stdscr ) ) };

    int i = 0;
    for ( Block& block : blocks )
    {
        block = Block();
        block.setPosition( 1, i );
        block.setColorPair( Entity::ColorPair::Red );
        block.setAttribiutes( A_BOLD );
        block.draw();
        block.setPosition( i, 3 );
        block.draw();

        i++;
    }

    getch();

    Paddle paletka;
    paletka.setSize( 25 );
    paletka.setPosition( 25, 5 );
    paletka.draw();

    Ball ball;
    ball.setPosition( 5, 5 );
    ball.draw();

    getch();

    paletka.getBall( &ball );

    while ( true )
    {
        switch ( getch() )
        {
            case 'a':
                paletka.move( 0, -1 );
                break;
            case 'd':
                paletka.move( 0, 1 );
                break;
            case 'w':
                paletka.shoot();
                break;
            default:
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}
