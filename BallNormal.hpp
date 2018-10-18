#ifndef BALLNORMAL_H
#define BALLNORMAL_H

#include "Ball.hpp"
#include "BallState.hpp"

class BallNormal : public BallState
{
    public:
        void draw( const Ball* t_ball ) override
        {
            attron( COLOR_PAIR( t_ball->getColor() ) | t_ball->getAttributes() );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( t_ball->getSpeed() ) );
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override
        {
            if ( t_axis & Ball::ReflectionAxis::Vertical )
            {
                t_ball->setVectorY( -t_ball->getVelocity().y );
            }

            if ( t_axis & Ball::ReflectionAxis::Horizontal )
            {
                t_ball->setVectorX( -t_ball->getVelocity().x );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* entity ) const override
        {
            auto axis = Ball::ReflectionAxis::None;

            if ( ( t_ball->getx()                           <  entity->getx()    &&
                   t_ball->getx() + t_ball->getVelocity().x >= entity->getx() )  ||
                 ( t_ball->getx()                           >  entity->getx() + entity->getWidth() - 1     &&
                   t_ball->getx() + t_ball->getVelocity().x <= entity->getx() + entity->getWidth() - 1 ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Horizontal );
            }

            if ( ( t_ball->gety()                           <  entity->gety()    &&
                   t_ball->gety() + t_ball->getVelocity().y >= entity->gety() )  ||
                 ( t_ball->gety()                           >  entity->gety() + entity->getHeight() - 1    &&
                   t_ball->gety() + t_ball->getVelocity().y <= entity->gety() + entity->getHeight() - 1 ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Vertical );
            }

            return axis;
        }
};

#endif
