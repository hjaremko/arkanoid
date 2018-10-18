#ifndef PADDLESTATE_H
#define PADDLESTATE_H

#include "Paddle.hpp"
#include "BallState.hpp"

class PaddleState
{
    public:
        PaddleState() {};
        virtual ~PaddleState() {};
    
        virtual void draw( const Paddle* ) const = 0;
        virtual void secondaryAction( Paddle* ) = 0;
};

// class PaddleSticky : public PaddleState
// {
//     public:
//         PaddleSticky()
//         {
//             // Map::instance()->getPaddle()->getBall( Map::instance()->getBall( 0 ) );
//         }

//         void draw( const Paddle* t_paddle ) const override
//         {
//             attron( COLOR_PAIR( t_paddle->getColor() ) | t_paddle->getAttributes() );

//             for ( int i = 0; i < t_paddle->getHeight(); ++i )
//             {
//                 for ( int j = 0; j < t_paddle->getWidth(); ++j )
//                 {
//                     attron( COLOR_PAIR( Entity::ColorPair::Green ) | A_BOLD );
//                     mvprintw( t_paddle->gety()-1, t_paddle->getx() + j, "_" );
//                     mvprintw( t_paddle->gety(), t_paddle->getx()-1, "/" );
//                     mvprintw( t_paddle->gety(), t_paddle->getx() + t_paddle->getWidth(), "\\" );

//                     attrset( A_NORMAL );

//                     mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
//                 }
//             }

//             attrset( A_NORMAL );
//         }

//         void secondaryAction( Paddle* t_paddle ) override
//         {

//         }
// };


#endif
