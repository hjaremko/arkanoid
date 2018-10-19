#include "Entity.hpp"

void Entity::setPosition( const int t_y, const int t_x )
{
    m_position = Point( t_y, t_x );
}

void Entity::setPosition( const Point& t_pos )
{
    m_position = t_pos;
}

void Entity::setColorPair( const ColorPair t_color )
{
    m_color = static_cast<int>( t_color );
}

void Entity::setAttribiutes( const int t_attributes )
{
    m_attributes = t_attributes;
}

Point Entity::getPosition() const
{
    return m_position;
}

int Entity::gety() const
{
    return m_position.y;
}

int Entity::getx() const
{
    return m_position.x;
}

void Entity::sety( const int t_y )
{
    m_position.y = t_y;
}

void Entity::setx( const int t_x )
{
    m_position.x = t_x;
}

void Entity::setWidth( const int t_width )
{
    m_width = t_width;
}

void Entity::setHeight( const int t_height )
{
    m_height = t_height;
}

int Entity::getWidth() const
{
    return m_width;
}

int Entity::getHeight() const
{
    return m_height;
}

bool Entity::isDestroyable() const
{
    return true;
}

bool Entity::isCollidable() const
{
    return true;
}

int Entity::getColor() const
{
    return m_color;
}

int Entity::getAttributes() const
{
    return m_attributes;
}
