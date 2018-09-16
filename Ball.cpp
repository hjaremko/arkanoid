#include <curses.h>

#include "Ball.hpp"

Ball::Ball()
{

}

void Ball::draw() const
{
    attron( COLOR_PAIR( m_color ) | m_attributes );
    mvprintw( m_y, m_x, "O" );
    attrset( A_NORMAL );
    refresh();
}

void Ball::destroy() const
{
    mvprintw( m_y, m_x, " " );
    refresh();
}

void Ball::move( const int t_y, const int t_x )
{
    destroy();
    setPosition( m_y + t_y, m_x + t_x );
    draw();
}
