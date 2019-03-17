#ifndef BALLALLBREAKING_H
#define BALLALLBREAKING_H

#include "ball.hpp"
#include "ball_state.hpp"
#include "ball_normal.hpp"

class ball_allbreaking : public ball_normal
{
public:
    ball_allbreaking()
    {
        start_time = steady_clock::now();
    }

    void draw( const ball* t_ball ) override
    {
        auto end = std::chrono::steady_clock::now();
        auto left = duration -
                    duration_cast<seconds>( end - start_time ).count();

        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::red ) ) | A_BOLD );

        mvprintw( 2, 5, "*O  : %d", left );

        mvprintw( last_position.gety(), last_position.getx(), "*" );
        mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->get_look() );

        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        last_position = t_ball->get_position();

        t_ball->change_speed_by( -5 );
        t_ball->move_by( t_ball->get_velocity() );

        std::this_thread::sleep_for( milliseconds( t_ball->get_speed() ) );

        auto end = steady_clock::now();
        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            t_ball->set_state( new ball_normal );
        }
    }

    ball::reflection_axis get_reflection_axis( const ball* t_ball, entity* entity ) const override
    {
        auto axis = ball::reflection_axis::none;

        if ( dynamic_cast<paddle*>( entity ) ) //bad
        {
            axis = ball::reflection_axis::vertical;
        }
        else if ( dynamic_cast<unbreakable_block*>( entity ) )
        {
            axis = ball_normal::get_reflection_axis( t_ball, entity );
        }

        return axis;
    }

private:
    steady_clock::time_point start_time;
    point last_position;
    int duration{ 10 };
};

#endif
