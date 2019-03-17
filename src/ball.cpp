#include "ball.hpp"
#include "ball_normal.hpp"

ball::ball()
{
    m_state = new ball_normal;
}

void ball::draw() const
{
    m_state->draw( this );
}

void ball::move_by( int t_y, int t_x )
{
    set_position( gety() + t_y, getx() + t_x );
}

void ball::move_by( const point& t_point )
{
    set_position( get_position() + t_point );
}

void ball::shoot()
{
    m_state->shoot( this );
}

void ball::reflect( reflection_axis t_axis )
{
    m_state->reflect( this, t_axis );
}

bool ball::intersects( const point& t_point ) const
{
    return getx() == t_point.y && getx() == t_point.x;
}

point ball::get_velocity() const
{
    return m_velocity;
}

entity* ball::collides() const
{
    for ( auto& entity : map::instance()->get_entities() )
    {
        if ( entity->intersects( get_position() + get_velocity() ) )
        {
            return entity;
        }
    }

    return nullptr;
}

ball::reflection_axis ball::get_reflection_axis( entity* entity ) const
{
    return m_state->get_reflection_axis( this, entity );
}

ball::reflection_axis ball::get_wall_reflection_axis() const
{
    auto axis = reflection_axis::none;
    auto nextPosition = get_position() + get_velocity();

    if ( ( nextPosition.x >= getmaxx( stdscr ) || nextPosition.x < 0 ) )
    {
        axis = static_cast<reflection_axis>( axis | reflection_axis::horizontal );
    }

    if ( nextPosition.y < 0 )
    {
        axis = static_cast<reflection_axis>( axis | reflection_axis::vertical );
    }

    return axis;
}

int ball::get_speed() const
{
    return m_speed;
}

void ball::set_speed( int t_speed )
{
    m_speed = t_speed;
}

void ball::change_speed_by( int t_value )
{
    m_speed += t_value;

    if ( m_speed < MIN_SPEED )
    {
        m_speed = MIN_SPEED;
    }
}

char ball::get_look() const
{
    return m_look;
}

void ball::set_velocity( const point& t_velocity )
{
    m_velocity = t_velocity;
}

void ball::set_vectorY( int t_value )
{
    m_velocity.y = t_value;
}

void ball::set_vectorX( int t_value )
{
    m_velocity.x = t_value;
}

void ball::set_state( ball_state* t_state )
{
    m_state->set_state( this, t_state );
}

ball_state* ball::get_state() const
{
    return m_state;
}

void ball::set_stopped( const bool t_stop )
{
    m_stopped = t_stop;
}

bool ball::is_stopped() const
{
    return m_stopped;
}

// double moveFunction( point a, point b, double x ) const
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