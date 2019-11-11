#include "block.hpp"

block::block( color_pair t_color, chtype t_attributes, const point& t_point = point( 0, 0 ) )
{
    set_color( t_color );
    set_attributes( t_attributes );
    entity::set_position( t_point );
}

void block::draw() const
{
    attron( COLOR_PAIR( m_color ) | m_attributes );

    for ( int i = 0; i < m_height; ++i )
    {
        for ( int j = 0; j < m_width; ++j )
        {
            mvprintw( gety() + i, getx() + j, "%c", m_look );
        }
    }

    attrset( A_NORMAL );
}

void block::set_look( char t_look )
{
    m_look = t_look;
}
