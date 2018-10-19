#include "Paddle.hpp"
#include "BallMovement.hpp"
#include "PaddleNormal.hpp"

Paddle::Paddle()
{
    m_isDestroyable = false;
    m_state = new PaddleNormal;
}

Paddle::~Paddle()
{
    delete m_state;

    if ( m_ball )
    {
        delete m_ball;
    }
}

void Paddle::draw() const
{
    m_state->draw( this );
}

void Paddle::move( const int t_y, const int t_x )
{
    setPosition( Point( gety() + t_y, getx() + t_x ) );

    if ( m_ball )
    {
        m_ball->setPosition( Point( m_ball->gety() - 1, m_ball->getx() + t_x ) );
    }
}

Ball* Paddle::getBall( Ball* t_ball )
{
    m_ball = t_ball;
    m_ball->setStopped( true );

    return m_ball;
}

void Paddle::shoot()
{
    if ( m_ball )
    {
        m_ball->setStopped( false );
        BallMovement bm( m_ball );
        std::thread shootingThread( bm );
        shootingThread.detach();
        m_ball = nullptr;
    }
}

void Paddle::secondaryAction()
{
    m_state->secondaryAction( this );
}

void Paddle::setPosition( const Point& t_pos )
{
    if ( m_ball )
    {
        m_ball->moveBy( 0, t_pos.getx() - getx() );
    }

    Entity::setPosition( t_pos );
}

void Paddle::setPosition( const int t_y, const int t_x )
{
    if ( m_ball )
    {
        m_ball->moveBy( 0, t_x - getx() );
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
    return gety() == t_point.y && t_point.x >= getx() &&
           t_point.x < ( getx() + getWidth() );
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
