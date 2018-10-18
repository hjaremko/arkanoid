#ifndef BALLSTATE_H
#define BALLSTATE_H

#include <chrono>

#include "Map.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

class BallState
{
    public:
        virtual ~BallState() {}

        virtual void draw( const Ball* ) = 0;
        virtual void shoot( Ball* ) = 0;
        virtual void reflect( Ball*, Ball::ReflectionAxis ) = 0;
        virtual Ball::ReflectionAxis getReflectionAxis( const Ball*, Entity* ) const = 0;
 
        virtual bool isNull() const
        {
            return m_null;
        }

    private:
        bool m_null{ false };
};











#endif
