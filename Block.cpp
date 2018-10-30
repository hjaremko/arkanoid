#include "Block.hpp"

Block::Block()
{

} //ctor

Block::Block( ColorPair t_color, chtype t_attributes, const Point& t_point = Point( 0, 0 ) )
{
    setColorPair( t_color );
    setAttribiutes( t_attributes );
    Entity::setPosition( t_point );
}

void Block::draw() const
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

void Block::setLook( char t_look )
{
    m_look = t_look;
}
