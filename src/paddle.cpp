#include "paddle/paddle.hpp"

#include "paddle/paddle_normal.hpp"

#include <utility>

paddle::paddle() : state_( std::make_unique<paddle_normal>() )
{
}

void paddle::draw() const
{
    state_->draw( *this );

    for ( auto& ball : balls_ )
    {
        ball->draw();
    }
}

void paddle::catch_ball( paddle::ball_ptr ball )
{
    ball->set_stopped( true );
    //    ball->set_speed( ball::DEF_SPEED );
    ball->reflect( ball->get_reflection_axis( *this ) );
    balls_.insert( std::move( ball ) );
}

auto paddle::release_balls() -> std::unordered_set<paddle::ball_ptr>
{
    for ( auto& ball : balls_ )
    {
        ball->set_stopped( false );
    }

    return std::move( balls_ );
}

auto paddle::secondary_action() -> std::any
{
    return state_->secondary_action( *this );
}

void paddle::set_position( const point& pos )
{
    for ( auto& ball : balls_ )
    {
        ball->move_by( 0, pos.getx() - getx() );
    }

    entity::set_position( pos );
}

void paddle::set_position( int y, int x )
{
    for ( auto& ball : balls_ )
    {
        ball->move_by( 0, x - getx() );
    }

    entity::set_position( y, x );
}

void paddle::set_width( int width )
{
    width_ = width;
}

auto paddle::width() const -> int
{
    return width_;
}

auto paddle::intersects( const point& point ) const -> bool
{
    return state_->intersects( *this, point );
}

void paddle::set_state( paddle::state_ptr state )
{
    state_ = std::move( state );
}

void paddle::change_size_by( const int value )
{
    set_width( width() + value );

    if ( width() < MIN_WIDTH )
    {
        set_width( MIN_WIDTH );
    }
    else if ( width() > MAX_WIDTH )
    {
        set_width( MAX_WIDTH );
    }
}

auto paddle::is_destroyable() const -> bool
{
    return false;
}

auto make_paddle() -> paddle
{
    auto paddle_ { paddle {} };
    paddle_.set_width( 15 );
    paddle_.set_height( 1 );
    paddle_.set_position( getmaxy( stdscr ) - 5, getmaxx( stdscr ) / 2 - 7 );

    auto tmp = std::make_unique<ball>();
    tmp->set_position( paddle_.gety() - 1,
                       paddle_.getx() + paddle_.width() / 2 );
    paddle_.catch_ball( std::move( tmp ) );

    return paddle_;
}
