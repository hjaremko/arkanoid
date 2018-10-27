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
            t_ball->moveBy( t_ball->getVelocity() );

            std::this_thread::sleep_for(
                std::chrono::milliseconds( t_ball->getSpeed() ) );
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
            auto currentPosition = t_ball->getPosition();
            auto nextPosition    = t_ball->getPosition() + t_ball->getVelocity();
            auto entityStart     = entity->getPosition();
            auto entityEnd       = entity->getPosition() + Point( entity->getHeight() - 1,
                                                                  entity->getWidth()  - 1 );


            if ( ( currentPosition.x < entityStart.x && nextPosition.x >= entityStart.x ) ||
                 ( currentPosition.x > entityEnd.x   && nextPosition.x <= entityEnd.x ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Horizontal );
            }

            if ( ( currentPosition.y < entityStart.y && nextPosition.y >= entityStart.y ) ||
                 ( currentPosition.y > entityEnd.y   && nextPosition.y <= entityEnd.y ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Vertical );
            }

            return axis;
        }
};

#endif
