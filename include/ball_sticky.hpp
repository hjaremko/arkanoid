#ifndef BALLSTICKY_H
#define BALLSTICKY_H

#include "ball_state.hpp"
#include "ball_normal.hpp"

class ball_sticky : public ball_normal
{
    public:
        ball_sticky() = default;

        void draw( const ball* t_ball ) override
        {
            attron( COLOR_PAIR( static_cast<int>( entity::color_pair::green ) ) | A_BOLD );

            mvprintw( 2, 5, "O   : %d", m_uses );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );

            attrset( A_NORMAL );
        }

        void shoot( ball* t_ball ) override
        {
            ball_normal::shoot( t_ball );

            if ( m_uses <= 0 )
            {
                t_ball->set_state( new ball_normal );
            }
        }

        ball::reflection_axis get_reflection_axis( const ball* t_ball, entity* t_entity ) const override
        {
            if ( dynamic_cast<paddle*>( t_entity ) ) //bad
            {
                map::instance()->get_paddle()->get_ball( const_cast<ball*>( t_ball ) );
                m_uses--;
            }

            return ball_normal::get_reflection_axis( t_ball, t_entity );
        }

    private:
        mutable int m_uses{ 5 };
};

#endif
