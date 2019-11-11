#ifndef PADDLEBARRIER_H
#define PADDLEBARRIER_H

#include "paddle.hpp"
#include "paddle_normal.hpp"

class paddle_barrier : public paddle_state
{
public:
    paddle_barrier()
    {
        start_time = steady_clock::now();

        m_barrier = new unbreakable_block( entity::color_pair::green, 0, point( getmaxy( stdscr ) - 2, 0 ) );
        m_barrier->set_width( getmaxx( stdscr ) );
        m_barrier->set_height( 1 );
        m_barrier->set_look( '~' );

        map::instance()->push_entity( m_barrier );
    }

    ~paddle_barrier() override
    {
        if ( m_barrier )
        {
            map::instance()->destroy( m_barrier );
        }
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

        attron( COLOR_PAIR( entity::color_pair::green ) | A_BOLD );

        mvprintw( 3, 5, "~~~ : %d", left );

        attrset( A_NORMAL );


        auto elapsed = duration_cast<seconds>( end - start_time ).count();

        if ( elapsed >= duration )
        {
            const_cast<paddle*>( t_paddle )->set_state( new paddle_normal );
            map::instance()->destroy( m_barrier );
        }

    }

    void secondary_action( paddle* ) override
    {
    }

private:
    steady_clock::time_point start_time;
    unbreakable_block* m_barrier{ nullptr };
    int duration{ 15 };
};

#endif
