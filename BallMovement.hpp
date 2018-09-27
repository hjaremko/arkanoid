#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include "Ball.hpp"

class BallMovement
{
    public:
        BallMovement( Ball* t_ball ) : m_ball( t_ball ) {}

        void operator()() const
        {
            while ( !m_ball->isOut() )
            {
                m_ball->shoot();
                m_ball->reflect( m_ball->out() );
                m_ball->reflect( m_ball->intersects() );
            }
        }

    private:
        Ball* m_ball{ nullptr };
};

#endif
