#include "Paddle.hpp"
#include "BallMovement.hpp"
#include "PaddleNormal.hpp"
#include "PaddleShooter.hpp"

Paddle::Paddle()
{
    // m_state = new PaddleNormal;
    m_state = new PaddleShooter;
}

Paddle::~Paddle()
{
    delete m_state;

    for ( auto& ball : m_balls )
    {
        ball = nullptr;
        delete ball;
    }

    m_balls.clear();
}

void Paddle::draw() const
{
    m_state->draw( this );
}

void Paddle::move( const int t_y, const int t_x )
{
    setPosition( Point( gety() + t_y, getx() + t_x ) );

    for ( auto& ball : m_balls )
    {
        ball->setPosition( ball->gety() - 1, ball->getx() + t_x );
    }
}

Ball* Paddle::getBall( Ball* t_ball )
{
    t_ball->setStopped( true );
    m_balls.push_back( t_ball );

    return t_ball;
}

void Paddle::shoot()
{
    for ( auto& ball : m_balls )
    {
        ball->setStopped( false );
        BallMovement bm( ball );
        std::thread shootingThread( bm );
        shootingThread.detach();
    }

    m_balls.clear();
}

void Paddle::secondaryAction()
{
    m_state->secondaryAction( this );
}

void Paddle::setPosition( const Point& t_pos )
{
    for ( auto& ball : m_balls )
    {
        ball->moveBy( 0, t_pos.getx() - getx() );
    }

    Entity::setPosition( t_pos );
}

void Paddle::setPosition( const int t_y, const int t_x )
{
    for ( auto& ball : m_balls )
    {
        ball->moveBy( 0, t_x - getx() );
    }

    Entity::setPosition( t_y, t_x );
}

void Paddle::setWidth( const int t_width )
{
    m_width = t_width;
}

int Paddle::getWidth() const
{
    return m_width;
}

bool Paddle::intersects( const Point& t_point ) const
{
    return gety() == t_point.y &&
           t_point.x >= getx() && t_point.x < ( getx() + getWidth() );
}

void Paddle::changeState( PaddleState* t_state )
{
    if ( m_state )
    {
        delete m_state;
    }

    m_state = t_state;
}

void Paddle::changeSizeBy( const int t_value )
{
    setWidth( getWidth() + t_value );

    if ( getWidth() < MIN_WIDTH )
    {
        setWidth( MIN_WIDTH );
    }
    else if ( getWidth() > MAX_WIDTH )
    {
        setWidth( MAX_WIDTH );
    }
}

bool Paddle::isDestroyable() const
{
    return false;
}
