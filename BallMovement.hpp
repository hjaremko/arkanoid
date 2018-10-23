#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include <mutex>

#include "Map.hpp"
#include "Ball.hpp"

extern std::mutex m;
int random( int min, int max );

class BallMovement
{
    public:
        explicit BallMovement( Ball* t_ball ) : m_ball( t_ball ) {}

        void operator()() const
        {
            while ( !m_ball->getPosition().isOut() && !m_ball->isStopped() )
            {
                m_ball->shoot();

                std::lock_guard<std::mutex> lock( m );

                auto entity = m_ball->collides();

                if ( entity && entity->isCollidable() )
                {
                    m_ball->reflect( m_ball->getReflectionAxis( entity ) );
                    m_ball->changeSpeedBy( -2 );

                    if ( entity->isDestroyable() )
                    {
                        Map::instance()->destroy( entity );

                        if ( random( 0, 10 ) == 0 )
                        {
                            Map::instance()->spawnPowerUp( m_ball->getPosition() );
                        }
                    }
                }
                else
                {
                    auto wallReflection = m_ball->getWallReflectionAxis();

                    if ( wallReflection != Ball::ReflectionAxis::None )
                    {
                        m_ball->reflect( m_ball->getWallReflectionAxis() );
                        m_ball->changeSpeedBy( -2 );
                    }
                }
            }

            if ( m_ball->getPosition().isOut() )
            {
                Map::instance()->destroyBall( m_ball );
            }
        }

    private:
        Ball* m_ball{ nullptr };
};

#endif
