#ifndef BALLSLOW_H
#define BALLSLOW_H

#include "Ball.hpp"
#include "BallState.hpp"

class BallSlow : public BallNormal
{
    public:
        BallSlow()
        {
            startTimePoint = steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = steady_clock::now();
            auto left = duration -
                        duration_cast<seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Yellow ) ) | A_BOLD );

            mvprintw( 2, 5, "O   : %d", left );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->moveBy( t_ball->getVelocity() );

            std::this_thread::sleep_for( milliseconds( 500 ) );

            auto end = steady_clock::now();
            auto elapsed = duration_cast<seconds>( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

    private:
        steady_clock::time_point startTimePoint;
        int  duration{ 10 };
};

#endif
