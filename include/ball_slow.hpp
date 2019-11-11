#ifndef BALLSLOW_H
#define BALLSLOW_H

#include "ball.hpp"
#include "ball_normal.hpp"

class ball_slow : public ball_normal
{
public:
    ball_slow()
    {
        start_time = steady_clock::now();
    }

    void draw( const ball* t_ball ) override
    {
        auto end = steady_clock::now();
        auto left = duration - duration_cast<seconds>( end - start_time ).count();

        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::yellow ) ) | A_BOLD );

        mvprintw( 2, 5, "O   : %d", left );
        mvprintw( t_ball->gety(), t_ball->getx(), "O" );

        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        t_ball->move_by( t_ball->get_velocity() );

        std::this_thread::sleep_for( milliseconds( 500 ) );

        auto end = steady_clock::now();
        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            t_ball->set_state( new ball_normal );
        }
    }

private:
    steady_clock::time_point start_time;
    int duration { 10 };
};

#endif
