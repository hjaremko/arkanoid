#ifndef BALLALLBREAKING_H
#define BALLALLBREAKING_H

#include "Ball.hpp"
#include "BallState.hpp"
#include "BallNormal.hpp"

class BallAllBreaking : public BallNormal
{
    public:
        BallAllBreaking()
        {
            startTimePoint = steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration -
                        duration_cast<seconds>( end - startTimePoint ).count();

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

            std::this_thread::sleep_for( milliseconds( t_ball->getSpeed() ) );

            auto end = steady_clock::now();
            auto elapsed = duration_cast<seconds>( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* entity ) const override
        {
            auto axis = Ball::ReflectionAxis::None;

            if ( dynamic_cast<Paddle*>( entity ) ) //bad
            {
                axis = Ball::ReflectionAxis::Vertical;
            }
            else if ( dynamic_cast<UnbreakableBlock*>( entity ) )
            {
                axis = BallNormal::getReflectionAxis( t_ball, entity );
            }

            return axis;
        }

    private:
        steady_clock::time_point startTimePoint;
        Point lastPosition;
        int   duration{ 10 };
};

#endif
