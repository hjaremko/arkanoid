#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include <cstdlib>
#include <ctime>

#include "Map.hpp"
#include "Ball.hpp"

class BallMovement
{
    public:
        explicit BallMovement( Ball* t_ball ) : m_ball( t_ball ) {}

        void operator()() const
        {
            srand( time( NULL ) );

            while ( !m_ball->isNull() && !m_ball->isStopped() )
            {
                m_ball->shoot();
                auto entity = m_ball->collides();

                if ( entity && entity->isCollidable() )
                {
                    m_ball->reflect( m_ball->getReflectionAxis( entity ) );
                    m_ball->changeSpeedBy( -2 );

                    if ( entity->isDestroyable() )
                    {
                        Map::instance()->destroy( entity );

                        if ( ( rand() % 10 ) == 0 )
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
        }

    private:
        Ball* m_ball{ nullptr };
};

#endif
