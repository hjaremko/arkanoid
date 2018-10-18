#ifndef BALLBULLET_H
#define BALLBULLET_H

#include "Ball.hpp"
#include "BallState.hpp"
#include "BallNull.hpp"

class BallBullet : public BallState
{
    public:
        void draw( const Ball* t_ball ) override
        {
            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::White ) ) | A_BOLD | t_ball->getAttributes() );
            mvprintw( t_ball->gety(), t_ball->getx(), "|" );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->setVectorX( 0 );
            t_ball->moveBy( t_ball->getVelocity().y, 0 );
            std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override
        {
            if ( t_axis != Ball::ReflectionAxis::None )
            {
                t_ball->changeState( new BallNull );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball*, Entity* ) const override
        {
            return Ball::ReflectionAxis::Horizontal;
        }
};

#endif
