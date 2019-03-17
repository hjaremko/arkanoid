#ifndef PADDLESTATE_H
#define PADDLESTATE_H

#include "paddle.hpp"
#include "ball_state.hpp"

class paddle_state
{
public:
    paddle_state() = default;
    virtual ~paddle_state() = default;
    virtual void draw( const paddle* ) const = 0;
    virtual void secondary_action( paddle* ) = 0;
};

// class PaddleSticky : public paddle_state
// {
//     public:
//         PaddleSticky()
//         {
//             // map::instance()->get_paddle()->get_ball( map::instance()->get_ball( 0 ) );
//         }

//         void draw( const paddle* t_paddle ) const override
//         {
//             attron( COLOR_PAIR( t_paddle->get_color() ) | t_paddle->get_attributes() );

//             for ( int i = 0; i < t_paddle->height(); ++i )
//             {
//                 for ( int j = 0; j < t_paddle->width(); ++j )
//                 {
//                     attron( COLOR_PAIR( entity::color_pair::green ) | A_BOLD );
//                     mvprintw( t_paddle->gety()-1, t_paddle->getx() + j, "_" );
//                     mvprintw( t_paddle->gety(), t_paddle->getx()-1, "/" );
//                     mvprintw( t_paddle->gety(), t_paddle->getx() + t_paddle->width(), "\\" );

//                     attrset( A_NORMAL );

//                     mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
//                 }
//             }

//             attrset( A_NORMAL );
//         }

//         void secondary_action( paddle* t_paddle ) override
//         {

//         }
// };


#endif
