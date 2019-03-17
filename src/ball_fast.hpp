#ifndef BALLFAST_H
#define BALLFAST_H

#include "ball.hpp"
#include "ball_normal.hpp"

class ball_fast : public ball_normal
{
public:
    ball_fast()
    {
        start_time = steady_clock::now();
    }

    void draw( const ball* t_ball ) override
    {
        auto end_time = steady_clock::now();
        auto time_left = duration -
                         duration_cast<seconds>( end_time - start_time ).count();

        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::magenta ) ) | A_BOLD );

        mvprintw( 2, 5, "O   : %d", time_left );
        mvprintw( t_ball->gety(), t_ball->getx(), "O" );

        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        t_ball->move_by( t_ball->get_velocity() );

        std::this_thread::sleep_for( milliseconds( 16 ) );

        auto end = steady_clock::now();
        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            t_ball->set_state( new ball_normal );
        }
    }

private:
    steady_clock::time_point start_time;
    int duration{ 5 };
};

#endif
