#ifndef WINDOWSEVENTHANDLERIMP_H
#define WINDOWSEVENTHANDLERIMP_H

#include <windows.h>

#include "Event.hpp"

class WindowsEventHandlerImp : public EventHandlerImp
{
    public:
        WindowsEventHandlerImp()
        {
            hStdin = GetStdHandle( STD_INPUT_HANDLE );
            if ( hStdin == INVALID_HANDLE_VALUE )
                ErrorExit( "GetStdHandle" );

            // Save the current input mode, to be restored on exit.
            if ( !GetConsoleMode( hStdin, &fdwSaveOldMode ) )
                ErrorExit( "GetConsoleMode" );

            // Enable the window and mouse input events.
            fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
            if ( !SetConsoleMode( hStdin, fdwMode ) )
                ErrorExit( "SetConsoleMode" );
        }

        ~WindowsEventHandlerImp()
        {
            SetConsoleMode( hStdin, fdwSaveOldMode );
        }

        VOID ErrorExit ( const char* lpszMessage )
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

        void MouseEventProc( MOUSE_EVENT_RECORD mer, Event& t_event )
        {
            #ifndef MOUSE_HWHEELED
            #define MOUSE_HWHEELED 0x0008
            #endif

            t_event.type = Event::Type::MouseButtonPressed;

            switch ( mer.dwEventFlags )
            {
                case 0:

                    if ( mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
                    {
                        t_event.mouseButton.button = Mouse::Button::Button1;
                    }
                    else if ( mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED )
                    {
                        t_event.mouseButton.button = Mouse::Button::Button3;
                    }

                    break;
                case DOUBLE_CLICK:
                case MOUSE_HWHEELED:
                case MOUSE_MOVED:
                    t_event.type        = Event::Type::MouseMoved;
                    t_event.mouseMove.y = mer.dwMousePosition.Y;
                    t_event.mouseMove.x = mer.dwMousePosition.X;
                    break;

                default:
                    break;
            }
        }

        bool devGetEvent( Event& t_event )
        {
            if ( !ReadConsoleInput (
                    hStdin,         // input buffer handle
                    irInBuf,        // buffer to read into
                    128,            // size of read buffer
                    &cNumRead ) )   // number of records read
                ErrorExit( "ReadConsoleInput" );

            for ( i = 0; i < cNumRead; ++i )
            {
                switch ( irInBuf[ i ].EventType )
                {
                    case KEY_EVENT: // keyboard input
                        // KeyEventProc( irInBuf[ i ].Event.KeyEvent );
                        if ( irInBuf[ i ].Event.KeyEvent.wVirtualKeyCode == 0x51 )
                        {
                            t_event.type     = Event::Type::KeyPressed;
                            t_event.key.code = Keyboard::Key::Q;
                        }

                        break;

                    case MOUSE_EVENT: // mouse input
                        MouseEventProc( irInBuf[ i ].Event.MouseEvent, t_event );

                        break;

                    // case WINDOW_BUFFER_SIZE_EVENT: // disregard scrn buf. resizing
                    // case FOCUS_EVENT:              // disregard focus events
                    // case MENU_EVENT:               // disregard menu events
                    default:
                        // ErrorExit("Unknown event type");
                        break;
                }

            }

            return cNumRead > 0;
        }

    private:
        HANDLE hStdin;
        DWORD  fdwSaveOldMode;
        DWORD  cNumRead;
        DWORD  fdwMode;
        DWORD  i;
        INPUT_RECORD irInBuf[ 128 ];
};

#endif
