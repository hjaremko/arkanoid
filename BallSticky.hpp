#ifndef BALLSTICKY_H
#define BALLSTICKY_H

#include "Ball.hpp"
#include "BallState.hpp"


class BallSticky : public BallNormal
{
    public:
        BallSticky()
        {
            startTimePoint = std::chrono::steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration - std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Green ) ) | A_BOLD | t_ball->getAttributes() );
            mvprintw( 2, 5, "O   : %d", left );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            BallNormal::shoot( t_ball );

            auto end = std::chrono::steady_clock::now();

            if ( std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count() >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* t_entity ) const override
        {
            if ( dynamic_cast<Paddle*>( t_entity ) )
            {
                Map::instance()->getPaddle()->getBall( const_cast<Ball*>( t_ball ) );
            }

            return BallNormal::getReflectionAxis( t_ball, t_entity );
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        int  duration{ 15 };
};

#endif
