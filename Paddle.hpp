#ifndef PADDLE_H
#define PADDLE_H

#include <thread>
#include <chrono>
#include <curses.h>

#include "Entity.hpp"
#include "Ball.hpp"
#include "Point.hpp"

class Paddle : public Entity
{
    public:
        Paddle();
        ~Paddle();
        void draw() const override;
        void move( const int, const int );

        Ball* getBall( Ball* t_ball )
        {
            m_ball = t_ball;
            m_ball->setPosition( Point( gety() - 1, getx() + static_cast<int>( getWidth() / 2 ) ) );

            return m_ball;
        }

        void shoot();

        void setPosition( const Point& t_pos )
        {
            Entity::setPosition( t_pos );

            if ( m_ball )
            {
                m_ball->setPosition( Point( gety() - 1, getx() + static_cast<int>( getWidth() / 2 ) ) );
            }
        }

        void setWidth( const int t_width )
        {
            m_width = t_width;
        }

        int getWidth() const
        {
            return m_width;
        }

        bool intersects( const Point& t_point ) const override
        {
            return gety() == t_point.y && t_point.x >= getx() && t_point.x < ( getx() + getWidth() );
        }

    private:
        Ball* m_ball{ nullptr };
};

#endif //PADDLE_H
