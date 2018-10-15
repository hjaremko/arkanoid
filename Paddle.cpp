#include "Paddle.hpp"
#include "BallMovement.hpp"
#include "PaddleState.hpp"

Paddle::Paddle()
{
    m_isDestroyable = false;
    m_state = new PaddleNormal;
    // m_state = new PaddleShooter;
    // m_state = new PaddleSticky;
}

Paddle::~Paddle()
{

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
        m_ball->setPosition( Point( gety() - 1, getx() +
                                    static_cast<int>( getWidth() / 2 ) ) );
    }
}

Ball* Paddle::getBall( Ball* t_ball )
{
    m_ball = t_ball;
    m_ball->setPosition( Point( gety() - 1, getx() + static_cast<int>( getWidth() / 2 ) ) );

    return m_ball;
}

void Paddle::shoot()
{
    if ( m_ball )
    {
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
    Entity::setPosition( t_pos );

    if ( m_ball )
    {
        m_ball->setPosition( Point( gety() - 1, getx() +
                                    static_cast<int>( getWidth() / 2 ) ) );
    }
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
