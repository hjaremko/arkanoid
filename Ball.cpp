#include "Ball.hpp"

Ball::Ball()
{

}

void Ball::draw() const
{
    // plot();

    attron( COLOR_PAIR( m_color ) | m_attributes );
    mvprintw( gety(), getx(), "%c", m_look );
    attrset( A_NORMAL );
}

void Ball::move( const int t_y, const int t_x )
{
    setPosition( gety() + t_y, getx() + t_x );
}

void Ball::shoot()
{
    setPosition( Point( gety() + getVelocity().y, getx() + getVelocity().x ) );

    std::this_thread::sleep_for( std::chrono::milliseconds( m_speed ) );
}

void Ball::reflect( ReflectionAxis t_axis )
{

    if ( t_axis == ReflectionAxis::Vertical )
    {
        m_velocity.y = -m_velocity.y;
    }
    else if ( t_axis == ReflectionAxis::Horizontal )
    {
        m_velocity.x = -m_velocity.x;
    }

    if ( m_speed > 40 && t_axis != ReflectionAxis::None )
    {
        m_speed -= 2;
    }
}

bool Ball::isOut() const
{
    return gety() < 0 || gety() > getmaxy( stdscr ) - 1 || getx() < 0 || getx() > getmaxx( stdscr ) - 1;
}

bool Ball::intersects( const Point& t_point ) const
{
    return getx() == t_point.y && getx() == t_point.x;
}

Vector2D Ball::getVelocity() const
{
    return m_velocity;
}

Ball::ReflectionAxis Ball::intersects()
{
    ReflectionAxis axis = ReflectionAxis::None;

    for ( auto& entity : *m_map )
    {
        if ( entity->intersects( Point( gety() + getVelocity().y, getx() + getVelocity().x ) ) )
        {
            if ( ( getx()                   <  entity->getx()    &&
                   getx() + getVelocity().x >= entity->getx() )  ||
                 ( getx()                   >  entity->getx() + entity->getWidth() - 1     &&
                   getx() + getVelocity().x <= entity->getx() + entity->getWidth() - 1 ) )
            {
                axis = ReflectionAxis::Horizontal;
            }

            if ( ( gety()                   <  entity->gety()    &&
                   gety() + getVelocity().y >= entity->gety() )  ||
                 ( gety()                   >  entity->gety() + entity->getHeight() - 1    &&
                   gety() + getVelocity().y <= entity->gety() + entity->getHeight() - 1 ) )
            {
                axis = ReflectionAxis::Vertical;
            }

            if ( entity->isDestroyable() )
            {
                destroy( entity );
            }
        }
    }

    return axis;
}

Ball::ReflectionAxis Ball::out() const
{
    if ( getx() + getVelocity().x >= getmaxx( stdscr ) || getx() + getVelocity().x < 0 )
        return ReflectionAxis::Horizontal;

    if ( gety() + getVelocity().y < 0 )
        return ReflectionAxis::Vertical;

    return ReflectionAxis::None;
}

void Ball::destroy( Entity* t_entity )
{
    auto pos = std::find( m_map->begin(), m_map->end(), t_entity );
    delete *pos;
    m_map->erase( pos );
}

// double moveFunction( Point a, Point b, double x ) const
// {
//     if ( ( a.x - b.x ) == 0 || ( a.x - b.x ) == 0 )
//     {
//         return 0;
//     }

//     return ( ( ( a.y - b.y ) / ( a.x - b.x ) ) * x + ( a.y - ( ( a.y - b.y ) / ( a.x - b.x ) ) * a.x ) );
// }

// void plot() const
// {
//     for ( int x = 0; x < getmaxx( stdscr ); ++x )
//     {
//         int y = round( moveFunction( startPos, second, x ) );

//         if ( y > 0 && y < getmaxy( stdscr ) - 1 )
//         {
//             mvprintw( y, x+1, "*" );
//         }
//     }
// }
// 
// bool areSame( double a, double b )
// {
//     return std::abs( a - b ) < 0.000001;
// }
// 