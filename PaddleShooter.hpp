#ifndef PADDLESHOOTER_H
#define PADDLESHOOTER_H

#include "Paddle.hpp"
#include "PaddleState.hpp"
#include "PaddleNormal.hpp"
#include "BallBullet.hpp"

class PaddleShooter : public PaddleState
{
    public:
        PaddleShooter()
        {
            startTimePoint = steady_clock::now();
        }

        void draw( const Paddle* t_paddle ) const override
        {
            auto end = steady_clock::now();
            auto left = duration -
                        duration_cast<seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( t_paddle->getColor() ) | t_paddle->getAttributes() );

            for ( int i = 0; i < t_paddle->getHeight(); ++i )
            {
                for ( int j = 0; j < t_paddle->getWidth(); ++j )
                {
                    mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
                }
            }

            attron( COLOR_PAIR( Entity::ColorPair::Cyan ) | A_BOLD );

            int mid = t_paddle->getx() + static_cast<int>( t_paddle->getWidth() / 2 );

            mvprintw( 3, 5, "$^$ : %d", left );
            // mvprintw( t_paddle->gety() - 1, mid,      "^"  );
            mvprintw( t_paddle->gety(),     mid - 1, "$^$" );
            mvprintw( t_paddle->gety(), t_paddle->getx(), "$" );
            mvprintw( t_paddle->gety(), t_paddle->getx() + t_paddle->getWidth() - 1, "$" );

            attrset( A_NORMAL );
        }

        void secondaryAction( Paddle* t_paddle ) override
        {

            auto ball = t_paddle->getBall( Map::instance()->newBall() );
            ball->setPosition( t_paddle->gety() - 1, t_paddle->getx() +
                               static_cast<int>( t_paddle->getWidth() / 2 ) );


            ball->changeState( new BallBullet );
            t_paddle->shoot();

            auto end = steady_clock::now();
            auto elapsed = duration_cast<seconds>( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                t_paddle->changeState( new PaddleNormal );
            }
        }

    private:
        steady_clock::time_point startTimePoint;
        int duration{ 5 };
};

#endif
