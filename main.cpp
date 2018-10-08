#include <curses.h>
#include <windows.h>
#include <stdio.h>

#include "Block.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Map.hpp"
#include "MapDrawing.hpp"
#include "BallState.hpp"

HANDLE hStdin;
DWORD  fdwSaveOldMode;
Map    map;

VOID ErrorExit ( const char* lpszMessage )
{
    fprintf( stderr, "%s\n", lpszMessage );

    // Restore input mode on exit.
    SetConsoleMode( ::hStdin, ::fdwSaveOldMode );
    endwin();
    ExitProcess( 0 );
}

// VOID KeyEventProc( KEY_EVENT_RECORD ker )
// {
//     // if( ker.bKeyDown )
//     //     printf("key pressed\n");
//     // else
//         // printf("key released\n");
// }

VOID MouseEventProc( MOUSE_EVENT_RECORD mer )
{
    #ifndef MOUSE_HWHEELED
    #define MOUSE_HWHEELED 0x0008
    #endif

    switch( mer.dwEventFlags )
    {
        case 0:

            if ( mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
            {
                map.getPaddle()->shoot();
            }
            else if( mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED )
            {
                auto ball = map.getPaddle()->getBall( map.newBall() );
                ball->changeState( new BallBullet );
                map.getPaddle()->shoot();
            }
            else
            {
                // printf("button press\n");
            }

            break;
        case DOUBLE_CLICK:
            break;
        case MOUSE_HWHEELED:
            break;
        case MOUSE_MOVED:
            map.getPaddle()->setPosition( Point( map.getPaddle()->gety(),
                                                 mer.dwMousePosition.X - ( map.getPaddle()->getWidth() / 2 ) ) );

            break;
        // case MOUSE_WHEELED:
        default:
            break;
    }
}

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

    map.initPaddle();
    map.initBlocks();

    MapDrawing mapDrawing( &map );
    std::thread drawingThread( mapDrawing );
    drawingThread.detach();

    DWORD cNumRead;
    DWORD fdwMode;
    DWORD i;
    INPUT_RECORD irInBuf[ 128 ];

    // Get the standard input handle.
    ::hStdin = GetStdHandle( STD_INPUT_HANDLE );
    if ( ::hStdin == INVALID_HANDLE_VALUE )
        ErrorExit( "GetStdHandle" );

    // Save the current input mode, to be restored on exit.
    if ( !GetConsoleMode( ::hStdin, &::fdwSaveOldMode ) )
        ErrorExit( "GetConsoleMode" );

    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if ( !SetConsoleMode( ::hStdin, fdwMode ) )
        ErrorExit( "SetConsoleMode" );

    // Loop to read and handle next input events.
    while ( true )
    {
        // Wait for the events.
        if ( !ReadConsoleInput (
                ::hStdin,       // input buffer handle
                irInBuf,        // buffer to read into
                128,            // size of read buffer
                &cNumRead ) )   // number of records read
            ErrorExit( "ReadConsoleInput" );

        // Dispatch the events to the appropriate handler.

        for ( i = 0; i < cNumRead; ++i )
        {
            switch( irInBuf[ i ].EventType )
            {
                case KEY_EVENT: // keyboard input
                    // KeyEventProc( irInBuf[ i ].Event.KeyEvent );
                    // ErrorExit( "Exit" );
                    if( irInBuf[ i ].Event.KeyEvent.bKeyDown )
                    {
                        endwin();
                        return 0;
                    }

                    break;

                case MOUSE_EVENT: // mouse input
                    MouseEventProc( irInBuf[ i ].Event.MouseEvent );
                    break;

                case WINDOW_BUFFER_SIZE_EVENT: // disregard scrn buf. resizing
                case FOCUS_EVENT:              // disregard focus events
                    SetCursor(NULL);
                    break;
                case MENU_EVENT:               // disregard menu events
                    break;

                // default:
                    // ErrorExit("Unknown event type");
                    // break;
            }
        }
    }

    // Restore input mode on exit.
    SetConsoleMode( ::hStdin, ::fdwSaveOldMode );
    endwin();

    return 0;
}
