#include "block.hpp"

#include <curses.h>

block::block( color_pair color,
              chtype attributes,
              const point& point = { 0, 0 } )
{
    set_color( color );
    set_attributes( attributes );
    entity::set_position( point );
}

void block::draw() const
{
    attron( COLOR_PAIR( color_ ) | attributes_ );

    for ( int i = 0; i < height_; ++i )
    {
        for ( int j = 0; j < width_; ++j )
        {
            mvprintw( gety() + i, getx() + j, "%c", look_ );
        }
    }

    attrset( A_NORMAL );
}

void block::set_look( char look )
{
    look_ = look;
}
