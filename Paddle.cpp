#include "Paddle.hpp"
#include "BallMovement.hpp"

Paddle::Paddle()
{
    m_isDestroyable = false;
}

Paddle::~Paddle()
{

}

void Paddle::draw() const
{
    attron( COLOR_PAIR( m_color ) | m_attributes );

    for ( int i = 0; i < m_height; ++i )
    {
        for ( int j = 0; j < m_width; ++j )
        {
            mvprintw( gety(), getx() + j, "@" );
        }
    }

    attrset( A_NORMAL );

    // int mid = getx() + static_cast<int>( m_width / 2 );

    // for ( int y = 0; y < getmaxy( stdscr ); ++y )
    // {
    //     mvprintw( y, mid, "|" );
    // }
}

void Paddle::move( const int t_y, const int t_x )
{
    setPosition( Point( gety() + t_y, getx() + t_x ) );

    if ( m_ball )
    {
        m_ball->setPosition( Point( gety() - 1, getx() + static_cast<int>( getWidth() / 2 ) ) );
    }
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
