#include "Ball.hpp"
#include "BallState.hpp"

Ball::Ball()
{

}

Ball::Ball( std::vector<Entity*>* t_map ) : m_map( t_map )
{
    m_state = new BallNormal;
}

void Ball::draw() const
{
    m_state->draw( this );
}

void Ball::moveBy( const int t_y, const int t_x )
{
    setPosition( gety() + t_y, getx() + t_x );
}

void Ball::shoot()
{
    moveBy( getVelocity().y, getVelocity().x );
    std::this_thread::sleep_for( std::chrono::milliseconds( getSpeed() ) );
}

void Ball::reflect( ReflectionAxis t_axis )
{
    m_state->reflect( this, t_axis );
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
    return m_state->intersects( this );
}

Ball::ReflectionAxis Ball::out() const
{
    if ( getx() + getVelocity().x >= getmaxx( stdscr ) || getx() + getVelocity().x < 0 )
    {
        return ReflectionAxis::Horizontal;
    }

    if ( gety() + getVelocity().y < 0 )
    {
        return ReflectionAxis::Vertical;
    }

    return ReflectionAxis::None;
}

void Ball::destroy( Entity* t_entity )
{
    auto pos = std::find( m_map->begin(), m_map->end(), t_entity );
    delete *pos;
    m_map->erase( pos );
}

int Ball::getSpeed() const
{
    return m_speed;
}

void Ball::setSpeed( const int t_speed )
{
    m_speed = t_speed;
}

void Ball::changeSpeedBy( const int t_value )
{
    m_speed += t_value;
}

char Ball::getLook() const
{
    return m_look;
}

void Ball::setVelocity( Vector2D& t_velocity )
{
    m_velocity = t_velocity;
}

void Ball::setVectorY( int t_value )
{
    m_velocity.y = t_value;
}

void Ball::setVectorX( int t_value )
{
    m_velocity.x = t_value;
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