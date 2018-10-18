#ifndef BALLSLOW_H
#define BALLSLOW_H

#include "Ball.hpp"
#include "BallState.hpp"

class BallSlow : public BallNormal
{
    public:
        BallSlow()
        {
            startTimePoint = std::chrono::steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration - std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Yellow ) ) | A_BOLD | t_ball->getAttributes() );
            mvprintw( 2, 5, "O   : %d", left );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

            auto end = std::chrono::steady_clock::now();

            if ( std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count() >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        int  duration{ 10 };
};

#endif
