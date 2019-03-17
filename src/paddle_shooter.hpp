#ifndef PADDLESHOOTER_H
#define PADDLESHOOTER_H

#include "paddle.hpp"
#include "paddle_state.hpp"
#include "paddle_normal.hpp"
#include "ball_bullet.hpp"

class paddle_shooter : public paddle_state
{
public:
    paddle_shooter()
    {
        start_time = steady_clock::now();
    }

    void draw( const paddle* t_paddle ) const override
    {
        auto end = steady_clock::now();
        auto left = duration -
                    duration_cast<seconds>( end - start_time ).count();

        attron( COLOR_PAIR( t_paddle->get_color() ) | t_paddle->get_attributes() );

        for ( int i = 0; i < t_paddle->height(); ++i )
        {
            for ( int j = 0; j < t_paddle->width(); ++j )
            {
                mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
            }
        }

        attron( COLOR_PAIR( entity::color_pair::cyan ) | A_BOLD );

        int mid = t_paddle->getx() + static_cast<int>( t_paddle->width() / 2 );

        mvprintw( 3, 5, "$^$ : %d", left );
        // mvprintw( t_paddle->gety() - 1, mid,      "^"  );
        mvprintw( t_paddle->gety(), mid - 1, "$^$" );
        mvprintw( t_paddle->gety(), t_paddle->getx(), "$" );
        mvprintw( t_paddle->gety(), t_paddle->getx() + t_paddle->width() - 1, "$" );

        attrset( A_NORMAL );


        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            const_cast<paddle*>( t_paddle )->set_state( new paddle_normal );
        }
    }

    void secondary_action( paddle* t_paddle ) override
    {
        auto ball = t_paddle->get_ball( map::instance()->new_ball() );
        ball->set_position( t_paddle->gety() - 1, t_paddle->getx() +
                                                  static_cast<int>( t_paddle->width() / 2 ) );


        ball->set_state( new ball_bullet );
        t_paddle->shoot();
    }

private:
    steady_clock::time_point start_time;
    int duration{ 5 };
};

#endif
