#ifndef PADDLE_H
#define PADDLE_H

#include <thread>
#include <chrono>

#include "Entity.hpp"
#include "Ball.hpp"

class ShootingBall
{
    public:
        ShootingBall( Ball* t_ball ) : m_ball( t_ball ) {}

        void operator()() const
        {
            m_ball->shoot();
        }

    private:
        Ball* m_ball{ nullptr };
};

class Paddle : public Entity
{
    public:
        Paddle();
        void draw() const;
        void destroy() const;
        // void shrink( int );
        // void enlarge( int );
        void setSize( const int );
        void move( const int, const int );

        void getBall( Ball* t_ball )
        {
            m_ball = t_ball;
            m_ball->destroy();
            m_ball->setPosition( m_y - 1, m_x + static_cast<int>( m_size / 2 ) );
        }

        void shoot()
        {
            if ( m_ball )
            {
                ShootingBall sb( m_ball );
                std::thread shootingThread( sb );
                shootingThread.detach();
                m_ball = nullptr;
            }
        }

    private:
        int m_size{ 1 };
        Ball* m_ball{ nullptr };
};

#endif //PADDLE_H
