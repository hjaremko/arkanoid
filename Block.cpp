#include <curses.h>

#include "Block.hpp"

Block::Block()
{

} //ctor

void Block::draw() const
{
    attron( COLOR_PAIR( m_color ) | m_attributes );
    mvprintw( m_y, m_x, "#" );
    attrset( A_NORMAL );
    refresh();
}

void Block::destroy() const
{
    mvprintw( m_y, m_x, " " );
    refresh();
}
