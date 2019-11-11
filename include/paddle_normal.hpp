#ifndef PADDLENORMAL_H
#define PADDLENORMAL_H

#include "paddle.hpp"
#include "paddle_state.hpp"

class paddle_normal : public paddle_state
{
public:
    void draw( const paddle* t_paddle ) const override
    {
        attron( COLOR_PAIR( t_paddle->get_color() ) | t_paddle->get_attributes() );

        for ( int i = 0; i < t_paddle->height(); ++i )
        {
            for ( int j = 0; j < t_paddle->width(); ++j )
            {
                mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
            }
        }

        attrset( A_NORMAL );
    }

    void secondary_action( paddle* ) override
    {
    }
};

#endif
