#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include "ball.hpp"
#include "map.hpp"

#include <mutex>

extern std::mutex m;
int random( int min, int max );

class ball_movement
{
public:
    explicit ball_movement( ball* t_ball ) : m_ball( t_ball )
    {
    }

    void operator()() const
    {
        while ( !m_ball->get_position().is_out() && !m_ball->is_stopped() )
        {
            m_ball->shoot();
            std::lock_guard<std::mutex> lock( m );

            auto entity = m_ball->collides();

            if ( entity && entity->is_collideable() )
            {
                m_ball->reflect( m_ball->get_reflection_axis( entity ) );
                m_ball->change_speed_by( -2 );

                if ( entity->is_destroyable() )
                {
                    map::instance()->destroy( entity );

                    if ( random( 0, 10 ) == 0 )
                    {
                        map::instance()->spawn_power( m_ball->get_position() );
                    }
                }
            }
            else
            {
                auto wall_reflection = m_ball->get_wall_reflection_axis();

                if ( wall_reflection != ball::reflection_axis::none )
                {
                    m_ball->reflect( m_ball->get_wall_reflection_axis() );
                    m_ball->change_speed_by( -2 );
                }
            }
        }

        if ( m_ball->get_position().is_out() ) // TODO: ball->is_out()
        {
            map::instance()->destroy_ball( m_ball );
        }
    }

private:
    ball* m_ball { nullptr };
};

#endif
