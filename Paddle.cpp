#include <curses.h>

#include "Paddle.hpp"

Paddle::Paddle()
{

}

void Paddle::draw() const
{
    attron( COLOR_PAIR( m_color ) | m_attributes );

    for ( int i = 0; i < m_size; ++i )
    {
        mvprintw( m_y, m_x + i, "*" );
    }

    attrset( A_NORMAL );
    refresh();

    if ( m_ball )
    {
        m_ball->draw();
    }
}

void Paddle::destroy() const
{
    for ( int i = 0; i < m_size; ++i )
    {
        mvprintw( m_y, m_x + i, " " );
    }

    refresh();

    if ( m_ball )
    {
        m_ball->destroy();
    }
}

// void Paddle::shrinkBy( const int t_value )
// {
//     setSize( m_size )
// }

// void Paddle::enlargeBy( int t_value )
// {

// }

void Paddle::setSize( const int t_size )
{
    m_size = t_size;
}

void Paddle::move( const int t_y, const int t_x )
{
    destroy();
    setPosition( m_y + t_y, m_x + t_x );

    if ( m_ball )
    {
        m_ball->destroy();
        m_ball->setPosition( m_y - 1, m_x + static_cast<int>( m_size / 2 ) );
        // m_ball->draw();
    }
    
    draw();
}
