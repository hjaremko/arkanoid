#ifndef PADDLE_H
#define PADDLE_H

#include <thread>
#include <chrono>
#include <curses.h>

#include "Entity.hpp"
#include "Ball.hpp"
#include "Point.hpp"

class PaddleState;

class Paddle : public Entity
{
    public:
        Paddle();
        ~Paddle();
        void draw() const override;
        void move( const int, const int );
        Ball* getBall( Ball* );
        void shoot();
        void setPosition( const Point& );
        void setPosition( const int, const int );
        void setWidth( const int );
        int  getWidth() const;
        bool intersects( const Point& ) const override;
        void secondaryAction();
        void changeState( PaddleState* );
        void changeSizeBy( const int );

        static const int MAX_WIDTH = 37;
        static const int MIN_WIDTH = 5;
    private:
        Ball* m_ball{ nullptr };
        PaddleState* m_state{ nullptr };
};

#endif //PADDLE_H
