#ifndef BALLNORMAL_H
#define BALLNORMAL_H

#include "ball.hpp"
#include "ball_state.hpp"

#include <thread>

class ball_normal : public ball_state
{
public:
    void draw( const ball* t_ball ) override
    {
        attron( COLOR_PAIR( t_ball->get_color() ) | t_ball->get_attributes() );
        mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->get_look() );
        attrset( A_NORMAL );
    }

    void shoot( ball* t_ball ) override
    {
        t_ball->move_by( t_ball->get_velocity() );

        std::this_thread::sleep_for( milliseconds( t_ball->get_speed() ) );
    }

    void reflect( ball* t_ball, ball::reflection_axis t_axis ) override
    {
        if ( t_axis & ball::reflection_axis::vertical )
        {
            t_ball->set_vectorY( -t_ball->get_velocity().y );
        }

        if ( t_axis & ball::reflection_axis::horizontal )
        {
            t_ball->set_vectorX( -t_ball->get_velocity().x );
        }
    }

    ball::reflection_axis get_reflection_axis( const ball* t_ball, entity* entity ) const override
    {
        auto axis = ball::reflection_axis::none;
        auto current_position = t_ball->get_position();
        auto next_position = t_ball->get_position() + t_ball->get_velocity();
        auto entity_start = entity->get_position();
        auto entity_end =
            entity->get_position() + point( entity->height() - 1, entity->width() - 1 );

        if ( ( current_position.x < entity_start.x && next_position.x >= entity_start.x ) ||
             ( current_position.x > entity_end.x && next_position.x <= entity_end.x ) )
        {
            axis = static_cast<ball::reflection_axis>( axis | ball::reflection_axis::horizontal );
        }

        if ( ( current_position.y < entity_start.y && next_position.y >= entity_start.y ) ||
             ( current_position.y > entity_end.y && next_position.y <= entity_end.y ) )
        {
            axis = static_cast<ball::reflection_axis>( axis | ball::reflection_axis::vertical );
        }

        return axis;
    }
};

#endif
