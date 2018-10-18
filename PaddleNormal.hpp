#ifndef PADDLENORMAL_H
#define PADDLENORMAL_H

#include "Paddle.hpp"
#include "PaddleState.hpp"


class PaddleNormal : public PaddleState
{
    public:
        void draw( const Paddle* t_paddle ) const override
        {
            attron( COLOR_PAIR( t_paddle->getColor() ) | t_paddle->getAttributes() );

            for ( int i = 0; i < t_paddle->getHeight(); ++i )
            {
                for ( int j = 0; j < t_paddle->getWidth(); ++j )
                {
                    mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
                }
            }

            attrset( A_NORMAL );
        }

        void secondaryAction( Paddle* t_paddle ) override
        {

        }
};

#endif
