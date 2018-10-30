#ifndef BALLWEIRD_H
#define BALLWEIRD_H

#include "Ball.hpp"
#include "BallNormal.hpp"

int random( int min, int max );

class BallWeird : public BallNormal
{
    public:
        BallWeird()
        {
            startTimePoint = steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = steady_clock::now();
            auto left = duration -
                        duration_cast<seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Cyan ) ) );

            mvprintw( 2, 5, "O   : %d", left );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            BallNormal::shoot( t_ball );

            auto end = steady_clock::now();
            auto elapsed = duration_cast<seconds>( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                t_ball->changeState( new BallNormal );
            }

        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* entity ) const override
        {
            auto axis = random( Ball::ReflectionAxis::Horizontal, Ball::ReflectionAxis::None - 1 );

            if ( dynamic_cast<Paddle*>( entity ) )
            {
                axis = Ball::ReflectionAxis::Vertical;
            }

            return static_cast<Ball::ReflectionAxis>( axis );
        }

    private:
        steady_clock::time_point startTimePoint;
        Point lastPosition;
        int   duration{ 20 };
};

#endif
