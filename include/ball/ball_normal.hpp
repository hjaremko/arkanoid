#ifndef BALLNORMAL_H
#define BALLNORMAL_H

#include "ball.hpp"
#include "ball_state.hpp"
#include "system_clock.hpp"

#include <thread>

class ball_normal : public ball_state
{
public:
    void draw( const ball& ball ) override
    {
        attron( COLOR_PAIR( ball.get_color() ) | ball.get_attributes() );
        mvprintw( ball.gety(), ball.getx(), "%c", ball.get_look() );
        attrset( A_NORMAL );
    }

    void shoot( ball& ball ) override
    {
        const auto current_tick = arkanoid::system_clock::ticks;

        if ( current_tick - last_tick_ >= ball.get_speed() )
        {
            ball.move_by( ball.get_velocity() );
            last_tick_ = current_tick;
        }
    }

    void reflect( ball& ball, ball::reflection_axis axis ) override
    {
        if ( axis & ball::reflection_axis::vertical )
        {
            ball.set_vectorY( -ball.get_velocity().y );
        }

        if ( axis & ball::reflection_axis::horizontal )
        {
            ball.set_vectorX( -ball.get_velocity().x );
        }
    }

    [[nodiscard]] auto get_reflection_axis( const ball& ball,
                                            const entity& entity ) const
        -> ball::reflection_axis override
    {
        auto axis = ball::reflection_axis::none;
        auto current_position = ball.get_position();
        auto next_position = ball.get_position() + ball.get_velocity();
        auto entity_start = entity.get_position();
        auto entity_end = entity.get_position() +
                          point( entity.height() - 1, entity.width() - 1 );

        if ( ( current_position.x < entity_start.x &&
               next_position.x >= entity_start.x ) ||
             ( current_position.x > entity_end.x &&
               next_position.x <= entity_end.x ) )
        {
            axis = static_cast<ball::reflection_axis>(
                axis | ball::reflection_axis::horizontal );
        }

        if ( ( current_position.y < entity_start.y &&
               next_position.y >= entity_start.y ) ||
             ( current_position.y > entity_end.y &&
               next_position.y <= entity_end.y ) )
        {
            axis = static_cast<ball::reflection_axis>(
                axis | ball::reflection_axis::vertical );
        }

        return axis;
    }

protected:
    arkanoid::system_clock::ticks_type last_tick_ { 0 };
};

#endif
