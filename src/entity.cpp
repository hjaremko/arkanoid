#include "entity.hpp"

void entity::set_position( int t_y, int t_x )
{
    m_position = point( t_y, t_x );
}

void entity::set_position( const point& t_pos )
{
    m_position = t_pos;
}

void entity::set_color( color_pair t_color )
{
    m_color = static_cast<int>( t_color );
}

void entity::set_attributes( chtype t_attributes )
{
    m_attributes = t_attributes;
}

point entity::get_position() const
{
    return m_position;
}

int entity::gety() const
{
    return m_position.y;
}

int entity::getx() const
{
    return m_position.x;
}

void entity::sety( const int t_y )
{
    m_position.y = t_y;
}

void entity::setx( const int t_x )
{
    m_position.x = t_x;
}

void entity::set_width( int t_width )
{
    m_width = t_width;
}

void entity::set_height( int t_height )
{
    m_height = t_height;
}

int entity::width() const
{
    return m_width;
}

int entity::height() const
{
    return m_height;
}

bool entity::is_destroyable() const
{
    return true;
}

bool entity::is_collideable() const
{
    return true;
}

int entity::get_color() const
{
    return m_color;
}

chtype entity::get_attributes() const
{
    return m_attributes;
}
