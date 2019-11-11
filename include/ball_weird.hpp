#ifndef BALLWEIRD_H
#define BALLWEIRD_H

#include "ball.hpp"
#include "ball_normal.hpp"

int random( int min, int max );

class ball_weird : public ball_normal
{
public:
    ball_weird()
    {
        start_time = steady_clock::now();
    }

    void draw( const ball* t_ball ) override
    {
        auto end = steady_clock::now();
        auto left = duration - duration_cast<seconds>( end - start_time ).count();

        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::cyan ) ) );

        mvprintw( 2, 5, "O   : %d", left );
        mvprintw( t_ball->gety(), t_ball->getx(), "O" );

        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        ball_normal::shoot( t_ball );

        auto end = steady_clock::now();
        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            t_ball->set_state( new ball_normal );
        }
    }

    ball::reflection_axis get_reflection_axis( const ball*, entity* entity ) const override
    {
        auto axis = random( ball::reflection_axis::horizontal, ball::reflection_axis::none - 1 );

        if ( dynamic_cast<paddle*>( entity ) )
        {
            axis = ball::reflection_axis::vertical;
        }

        return static_cast<ball::reflection_axis>( axis );
    }

private:
    steady_clock::time_point start_time;
    int duration { 20 };
};

#endif
