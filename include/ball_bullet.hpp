#ifndef BALLBULLET_H
#define BALLBULLET_H

#include "ball.hpp"
#include "ball_state.hpp"

class ball_bullet : public ball_state
{
public:
    void draw( const ball* t_ball ) override
    {
        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::white ) ) | A_BOLD );
        mvprintw( t_ball->gety(), t_ball->getx(), "|" );
        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        t_ball->set_vectorX( 0 );
        t_ball->move_by( t_ball->get_velocity() );
        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
    }

    void reflect( ball* t_ball, ball::reflection_axis t_axis ) override
    {
        if ( t_axis != ball::reflection_axis::none )
        {
            t_ball->set_stopped( true );
            map::instance()->destroy_ball( t_ball );
        }
    }

    ball::reflection_axis get_reflection_axis( const ball*, entity* ) const override
    {
        return ball::reflection_axis::horizontal;
    }

    void set_state( ball*, ball_state* ) override
    {
    }
};

#endif
