#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <curses.h>

#include "entity.hpp"

class block : public entity
{
public:
    block() = default;
    block( color_pair, chtype, const point& );
    void draw() const override;
    void set_look( char );

    bool intersects( const point& t_point ) const override
    {
        return t_point.y >= gety() && t_point.y < ( gety() + height() ) &&
               t_point.x >= getx() && t_point.x < ( getx() + width() );
    }

private:
    char m_look{ '#' };
};

class unbreakable_block : public block
{
public:
    unbreakable_block( color_pair t_color, chtype t_attributes, const point& t_point = point( 0, 0 ) )
    {
        set_color( t_color );
        set_attributes( t_attributes );
        entity::set_position( t_point );
        set_look( 'X' );
    }

    bool is_destroyable() const override
    {
        return false;
    }
};

#endif //BLOCK_H
