#ifndef BALLNULL_H
#define BALLNULL_H

#include "Ball.hpp"
#include "BallState.hpp"

class BallNull : public BallState
{
    public:
        void draw( const Ball* t_ball ) override {}
        void shoot( Ball* t_ball ) override {}
        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override {}
        Ball::ReflectionAxis getReflectionAxis( const Ball*, Entity* ) const override {}

        bool isNull() const override
        {
            return true;
        }
};

#endif
