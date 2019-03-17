#ifndef WINDOWSEVENTHANDLERIMP_H
#define WINDOWSEVENTHANDLERIMP_H

#include <windows.h>

#include "event.hpp"

class windows_event_handler : public event_handler_imp
{
public:
    windows_event_handler()
    {
        hStdin = GetStdHandle( STD_INPUT_HANDLE );
        if ( hStdin == INVALID_HANDLE_VALUE )
        {
            ErrorExit( "GetStdHandle" );
        }

        // Save the current input mode, to be restored on exit.
        if ( !GetConsoleMode( hStdin, &fdwSaveOldMode ) )
        {
            ErrorExit( "GetConsoleMode" );
        }

        // Enable the window and mouse_button input events.
        fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
        if ( !SetConsoleMode( hStdin, fdwMode ) )
        {
            ErrorExit( "SetConsoleMode" );
        }
    }

    ~windows_event_handler()
    {
        SetConsoleMode( hStdin, fdwSaveOldMode );
    }

    VOID ErrorExit( const char* lpszMessage )
    {
        fprintf( stderr, "%s\n", lpszMessage );

        // Restore input mode on exit.
        SetConsoleMode( hStdin, fdwSaveOldMode );
        endwin();
        ExitProcess( 0 );
    }

    // VOID KeyEventProc( KEY_EVENT_RECORD ker )
    // {
    // if( ker.bKeyDown )
    //     printf("key pressed\n");
    // else
    //     printf("key released\n");
    // }

    void MouseEventProc( MOUSE_EVENT_RECORD mer, event& t_event )
    {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif

        t_event.type = event::type::mouse_pressed;

        switch ( mer.dwEventFlags )
        {
            case 0:

                if ( mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
                {
                    t_event.mouse_button.button = mouse::button::button1;
                }
                else if ( mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED )
                {
                    t_event.mouse_button.button = mouse::button::button3;
                }

                break;
            case DOUBLE_CLICK:
            case MOUSE_HWHEELED:
            case MOUSE_MOVED:
                t_event.type = event::type::mouse_moved;
                t_event.mouse_move.y = mer.dwMousePosition.Y;
                t_event.mouse_move.x = mer.dwMousePosition.X;
                break;

            default:
                break;
        }
    }

    bool dev_get_event( event& t_event )
    {
        if ( !ReadConsoleInput(
                hStdin,         // input buffer handle
                irInBuf,        // buffer to read into
                128,            // size of read buffer
                &cNumRead ) )
        {   // number of records read
            ErrorExit( "ReadConsoleInput" );
        }

        for ( i = 0; i < cNumRead; ++i )
        {
            switch ( irInBuf[ i ].EventType )
            {
                case KEY_EVENT: // keyboard input
                    // KeyEventProc( irInBuf[ i ].event.key_event );
                    if ( irInBuf[ i ].Event.KeyEvent.wVirtualKeyCode == 0x51 )
                    {
                        t_event.type = event::type::key_pressed;
                        t_event.key.code = keyboard::key::Q;
                    }

                    break;

                case MOUSE_EVENT: // mouse_button input
                    MouseEventProc( irInBuf[ i ].Event.MouseEvent, t_event );

                    break;

                    // case WINDOW_BUFFER_SIZE_EVENT: // disregard scrn buf. resizing
                    // case FOCUS_EVENT:              // disregard focus events
                    // case MENU_EVENT:               // disregard menu events
                default:
                    // ErrorExit("unknown event type");
                    break;
            }

        }

        return cNumRead > 0;
    }

private:
    HANDLE hStdin;
    DWORD fdwSaveOldMode;
    DWORD cNumRead;
    DWORD fdwMode;
    DWORD i;
    INPUT_RECORD irInBuf[128];
};

#endif
