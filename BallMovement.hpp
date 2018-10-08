 #ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include "Ball.hpp"

class BallMovement
{
    public:
        explicit BallMovement( Ball* t_ball ) : m_ball( t_ball ) {}

        void operator()() const
        {
            while ( !m_ball->isNull() )
            {
                m_ball->shoot();

                if ( auto entity = m_ball->collides() )
                {
                    m_ball->reflect( m_ball->getReflectionAxis( entity ) );
                    m_ball->changeSpeedBy( -2 );

                    if ( entity->isDestroyable() )
                    {
                        m_ball->destroy( entity );
                    }
                }
                else
                {
                    m_ball->reflect( m_ball->getWallReflectionAxis() );
                }
            }
        }

    private:
        Ball* m_ball{ nullptr };
};

#endif
