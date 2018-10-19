#ifndef BALLALLBREAKING_H
#define BALLALLBREAKING_H

#include "Ball.hpp"
#include "BallState.hpp"
#include "BallNormal.hpp"

class BallAllBreaking : public BallState
{
    public:
        BallAllBreaking()
        {
            startTimePoint = std::chrono::steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration -
                        std::chrono::duration_cast<std::chrono::seconds>
                        ( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Red ) ) | A_BOLD );

            mvprintw( 2, 5, "*O  : %d", left );

            mvprintw( lastPosition.gety(), lastPosition.getx(), "*" );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            lastPosition = t_ball->getPosition();

            t_ball->changeSpeedBy( -5 );
            t_ball->moveBy( t_ball->getVelocity() );

            std::this_thread::sleep_for(
                std::chrono::milliseconds( t_ball->getSpeed() ) );

            auto end = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>
                           ( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
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
            return ( dynamic_cast<Paddle*>( entity ) ) ? Ball::ReflectionAxis::Vertical : Ball::ReflectionAxis::None; //bad
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        Point lastPosition;
        int   duration{ 10 };
};

#endif
