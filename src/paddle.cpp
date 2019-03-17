#include "paddle.hpp"
#include "ball_movement.hpp"
#include "paddle_normal.hpp"
#include "paddle_barrier.hpp"

paddle::paddle()
{
    m_state = new paddle_normal;
}

paddle::~paddle()
{
    delete m_state;

    for ( auto& ball : m_balls )
    {
        delete ball;
        ball = nullptr;
    }

    m_balls.clear();
}

void paddle::draw() const
{
    m_state->draw( this );
}

void paddle::move( const int t_y, const int t_x )
{
    set_position( point( gety() + t_y, getx() + t_x ) );

    for ( auto& ball : m_balls )
    {
        ball->set_position( ball->gety() - 1, ball->getx() + t_x );
    }
}

ball* paddle::get_ball( ball* t_ball )
{
    t_ball->set_stopped( true );
    m_balls.push_back( t_ball );

    return t_ball;
}

void paddle::shoot()
{
    for ( auto& ball : m_balls )
    {
        ball->set_stopped( false );
        ball_movement bm( ball );
        std::thread shooting_thread( bm );
        shooting_thread.detach();
    }

    m_balls.clear();
}

void paddle::secondary_action()
{
    m_state->secondary_action( this );
}

void paddle::set_position( const point& t_pos )
{
    for ( auto& ball : m_balls )
    {
        ball->move_by( 0, t_pos.getx() - getx() );
    }

    entity::set_position( t_pos );
}

void paddle::set_position( int t_y, int t_x )
{
    for ( auto& ball : m_balls )
    {
        ball->move_by( 0, t_x - getx() );
    }

    entity::set_position( t_y, t_x );
}

void paddle::set_width( int t_width )
{
    m_width = t_width;
}

int paddle::width() const
{
    return m_width;
}

bool paddle::intersects( const point& t_point ) const
{
    return gety() == t_point.y &&
           t_point.x >= getx() && t_point.x < ( getx() + width() );
}

void paddle::set_state( paddle_state* t_state )
{
    delete m_state;
    m_state = t_state;
}

void paddle::change_size_by( const int t_value )
{
    set_width( width() + t_value );

    if ( width() < MIN_WIDTH )
    {
        set_width( MIN_WIDTH );
    }
    else if ( width() > MAX_WIDTH )
    {
        set_width( MAX_WIDTH );
    }
}

bool paddle::is_destroyable() const
{
    return false;
}
