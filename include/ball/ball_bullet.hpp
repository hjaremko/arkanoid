#ifndef BALLBULLET_H
#define BALLBULLET_H

#include "ball.hpp"
#include "ball_state.hpp"

class ball_bullet : public ball_state
{
public:
    void draw( const ball& ball ) override
    {
        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::white ) ) |
                A_BOLD );
        mvprintw( ball.gety(), ball.getx(), "|" );
        attrset( A_NORMAL );
    }

    void shoot( ball& ball ) override
    {
        ball.set_vectorX( 0 );
        ball.move_by( ball.get_velocity() );
    }

    void reflect( ball& ball, ball::reflection_axis axis ) override
    {
        if ( axis != ball::reflection_axis::none )
        {
            ball.set_stopped( true );
        }
    }

    [[nodiscard]] auto get_reflection_axis( const ball& /*unused*/,
                                            const entity& /*unused*/ ) const
        -> ball::reflection_axis override
    {
        return ball::reflection_axis::horizontal;
    }
};

#endif
