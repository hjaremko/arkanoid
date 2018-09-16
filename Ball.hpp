#ifndef BALL_H
#define BALL_H

#include <thread>
#include <chrono>
#include <curses.h>

#include "Entity.hpp"

class Ball : public Entity
{
    public:
        Ball();
        void draw() const;
        void destroy() const;
        void move( const int, const int );

        void shoot()
        {
            for ( int i = 0; true; ++i )
            {
                if ( mvinch( m_y + m_direction, m_x + m_angle ) == ' ' )
                {
                    mvprintw( 0, 0, "dir: %d  angl: %d    ", m_direction, m_angle );
                    move( m_direction, m_angle );
                    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
                }
                else
                {
                    mvprintw( m_y + m_direction, m_x + m_angle, " " ); //fix
                    refresh();

                    m_direction = -m_direction;

                    if ( mvinch( m_y + m_direction, m_x + m_angle ) != ' ' )
                    {
                        m_direction = -m_direction;
                        m_angle = -m_angle;
                    }

                }
            }
        }

    private:
        int m_angle{ 1 };
        int m_direction{ -1 };
};

#endif //BALL_H
