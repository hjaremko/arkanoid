#include "Ball.hpp"
#include "BallNormal.hpp"

Ball::Ball()
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

void Ball::moveBy( const Point& t_point )
{
    setPosition( getPosition() + t_point );
}

void Ball::shoot()
{
    m_state->shoot( this );
}

void Ball::reflect( ReflectionAxis t_axis )
{
    m_state->reflect( this, t_axis );
}

bool Ball::intersects( const Point& t_point ) const
{
    return getx() == t_point.y && getx() == t_point.x;
}

Point Ball::getVelocity() const
{
    return m_velocity;
}

Entity* Ball::collides() const
{
    for ( auto& entity : Map::instance()->getEntities() )
    {
        if ( entity->intersects( getPosition() + getVelocity() ) )
        {
            return entity;
        }
    }

    return nullptr;
}

Ball::ReflectionAxis Ball::getReflectionAxis( Entity* entity ) const
{
    return m_state->getReflectionAxis( this, entity );
}

Ball::ReflectionAxis Ball::getWallReflectionAxis() const
{
    auto axis = ReflectionAxis::None;
    auto nextPosition = getPosition() + getVelocity();

    if ( ( nextPosition.x >= getmaxx( stdscr ) || nextPosition.x < 0 ) )
    {
        axis = static_cast<ReflectionAxis>( axis | ReflectionAxis::Horizontal );
    }

    if ( nextPosition.y < 0 )
    {
        axis = static_cast<ReflectionAxis>( axis | ReflectionAxis::Vertical );
    }

    return axis;
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

    if ( m_speed < MIN_SPEED )
    {
        m_speed = MIN_SPEED;
    }
}

char Ball::getLook() const
{
    return m_look;
}

void Ball::setVelocity( const Point& t_velocity )
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

void Ball::changeState( BallState* t_state )
{
    m_state->changeState( this, t_state );
}

BallState* Ball::getState() const
{
    return m_state;
}

void Ball::setStopped( const bool t_stop )
{
    m_stopped = t_stop;
}

bool Ball::isStopped() const
{
    return m_stopped;
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