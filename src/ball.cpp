#include "ball/ball.hpp"

#include "ball/ball_normal.hpp"

ball::ball() : state_( std::make_shared<ball_normal>() )
{
}

void ball::draw() const
{
    state_->draw( *this );
}

void ball::move_by( int y, int x )
{
    set_position( gety() + y, getx() + x );
}

void ball::move_by( const point& point )
{
    move_by( point.y, point.x );
}

void ball::shoot()
{
    state_->shoot( *this );
}

void ball::reflect( reflection_axis axis )
{
    state_->reflect( *this, axis );
}

auto ball::intersects( const point& point ) const -> bool
{
    return getx() == point.y && getx() == point.x;
}

auto ball::get_velocity() const -> point
{
    return velocity_;
}

auto ball::get_reflection_axis( const entity& entity ) const
    -> ball::reflection_axis
{
    return state_->get_reflection_axis( *this, entity );
}

auto ball::get_wall_reflection_axis() const -> ball::reflection_axis
{
    auto axis = reflection_axis::none;
    auto nextPosition = get_position() + get_velocity();

    if ( ( nextPosition.x >= getmaxx( stdscr ) || nextPosition.x < 0 ) )
    {
        axis =
            static_cast<reflection_axis>( axis | reflection_axis::horizontal );
    }

    if ( nextPosition.y < 0 )
    {
        axis = static_cast<reflection_axis>( axis | reflection_axis::vertical );
    }

    return axis;
}

auto ball::get_speed() const -> arkanoid::system_clock::ticks_type
{
    return speed_;
}

void ball::set_speed( arkanoid::system_clock::ticks_type speed )
{
    speed_ = speed;

    if ( speed_ < MIN_SPEED )
    {
        speed_ = MIN_SPEED;
    }
}

void ball::change_speed_by( arkanoid::system_clock::ticks_type value )
{
    set_speed( speed_ + value );
}

 auto ball::get_look() const -> char
{
    return look_;
}

void ball::set_vectorY( int value )
{
    velocity_.y = value;
}

void ball::set_vectorX( int value )
{
    velocity_.x = value;
}

void ball::set_state( state_ptr state )
{
    state_ = std::move( state );
}

auto ball::get_state() const -> ball_state&
{
    return *state_;
}

void ball::set_stopped( const bool is_stopped )
{
    is_stopped_ = is_stopped;
}

auto ball::is_stopped() const -> bool
{
    return is_stopped_;
}
