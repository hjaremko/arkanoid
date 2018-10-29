#ifndef BALLSTICKY_H
#define BALLSTICKY_H

#include "Ball.hpp"
#include "BallState.hpp"


class BallSticky : public BallNormal
{
    public:
        BallSticky()
        {
        }

        void draw( const Ball* t_ball ) override
        {
            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Green ) ) | A_BOLD );

            mvprintw( 2, 5, "O   : %d", m_uses );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            BallNormal::shoot( t_ball );

            if ( m_uses <= 0 )
            {
                t_ball->changeState( new BallNormal );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* t_entity ) const override
        {
            if ( dynamic_cast<Paddle*>( t_entity ) ) //bad
            {
                Map::instance()->getPaddle()->getBall( const_cast<Ball*>( t_ball ) );
                m_uses--;
            }

            return BallNormal::getReflectionAxis( t_ball, t_entity );
        }

    private:
        mutable int m_uses{ 5 };
};

#endif
