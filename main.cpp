#include <curses.h>
#include <stdio.h>

#include "Block.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Map.hpp"
#include "MapDrawing.hpp"
#include "BallState.hpp"
#include "EventHandler.hpp"

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

    if ( has_colors() == FALSE )
    {  
        endwin();
        printf( "Your terminal does not support color\n" );

        return 1;
    }

    start_color();
    initColorPairs();

    Map map;
    map.initPaddle();
    map.initBlocks();

    MapDrawing  mapDrawing( &map );
    std::thread drawingThread( mapDrawing );
    drawingThread.detach();

    EventHandler eventHandler;
    Event        event;

    while ( true )
    {
        eventHandler.getEvent( event );

        switch ( event.type )
        {
            case Event::Type::KeyPressed:
            {
                if ( event.key.code == Keyboard::Key::Q )
                {
                    endwin();
                    return 0;
                }

                break;
            }

            case Event::Type::MouseButtonPressed:
            {
                switch ( event.mouseButton.button )
                {
                    case Mouse::Button::Button1:
                    {
                        map.getPaddle()->shoot();

                        break;
                    }

                    case Mouse::Button::Button3:
                    {
                        auto ball = map.getPaddle()->getBall( map.newBall() );
                        ball->changeState( new BallBullet );
                        map.getPaddle()->shoot();

                        break;
                    }

                    default:
                        break;
                }

                break;
            }

            case Event::Type::MouseMoved:
            {
                map.getPaddle()->setPosition(
                    Point( map.getPaddle()->gety(),
                    event.mouseMove.x - ( map.getPaddle()->getWidth() / 2 ) ) );

                break;
            }

            default:
                break;
        }
    }

    endwin();
    return 0;
}
