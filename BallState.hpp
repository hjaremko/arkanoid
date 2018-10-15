#ifndef BALLSTATE_H
#define BALLSTATE_H

#include <chrono>

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

class BallNormal : public BallState
{
    public:
        void draw( const Ball* t_ball ) override
        {
            attron( COLOR_PAIR( t_ball->getColor() ) | t_ball->getAttributes() );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( t_ball->getSpeed() ) );
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override
        {
            if ( t_axis & Ball::ReflectionAxis::Vertical )
            {
                t_ball->setVectorY( -t_ball->getVelocity().y );
            }

            if ( t_axis & Ball::ReflectionAxis::Horizontal )
            {
                t_ball->setVectorX( -t_ball->getVelocity().x );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* entity ) const override
        {
            auto axis = Ball::ReflectionAxis::None;

            if ( ( t_ball->getx()                           <  entity->getx()    &&
                   t_ball->getx() + t_ball->getVelocity().x >= entity->getx() )  ||
                 ( t_ball->getx()                           >  entity->getx() + entity->getWidth() - 1     &&
                   t_ball->getx() + t_ball->getVelocity().x <= entity->getx() + entity->getWidth() - 1 ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Horizontal );
            }

            if ( ( t_ball->gety()                           <  entity->gety()    &&
                   t_ball->gety() + t_ball->getVelocity().y >= entity->gety() )  ||
                 ( t_ball->gety()                           >  entity->gety() + entity->getHeight() - 1    &&
                   t_ball->gety() + t_ball->getVelocity().y <= entity->gety() + entity->getHeight() - 1 ) )
            {
                axis = static_cast<Ball::ReflectionAxis>( axis | Ball::ReflectionAxis::Vertical );
            }

            return axis;
        }
};

class BallAllBreaking : public BallState
{
    public:
        BallAllBreaking()
        {
            startTimePoint = std::chrono::steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration - std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Red ) ) | t_ball->getAttributes() | A_BOLD );

            mvprintw( 2, 5, "*O  : %d", left );

            mvprintw( lastPosition.gety(), lastPosition.getx(), "*" );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            lastPosition = t_ball->getPosition();
            t_ball->changeSpeedBy( -5 );

            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( t_ball->getSpeed() ) );

            auto end = std::chrono::steady_clock::now();

            if ( std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count() >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override
        {
            if ( t_axis & Ball::ReflectionAxis::Vertical )
            {
                t_ball->setVectorY( -t_ball->getVelocity().y );
            }

            if ( t_axis & Ball::ReflectionAxis::Horizontal )
            {
                t_ball->setVectorX( -t_ball->getVelocity().x );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball* t_ball, Entity* entity ) const override
        {
            return ( dynamic_cast<Paddle*>( entity ) ) ? Ball::ReflectionAxis::Vertical : Ball::ReflectionAxis::None; //bad
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        Point lastPosition;
        int   duration{ 10 };
};

class BallBullet : public BallState
{
    public:
        void draw( const Ball* t_ball ) override
        {
            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::White ) ) | A_BOLD | t_ball->getAttributes() );
            mvprintw( t_ball->gety(), t_ball->getx(), "|" );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->setVectorX( 0 );
            t_ball->moveBy( t_ball->getVelocity().y, 0 );
            std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis ) override
        {
            if ( t_axis != Ball::ReflectionAxis::None )
            {
                t_ball->changeState( new BallNull );
            }
        }

        Ball::ReflectionAxis getReflectionAxis( const Ball*, Entity* ) const override
        {
            return Ball::ReflectionAxis::Horizontal;
        }
};

class BallSlow : public BallNormal
{
    public:
        BallSlow()
        {
            startTimePoint = std::chrono::steady_clock::now();
        }

        void draw( const Ball* t_ball ) override
        {
            auto end = std::chrono::steady_clock::now();
            auto left = duration - std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( static_cast<int>( Entity::ColorPair::Yellow ) ) | A_BOLD | t_ball->getAttributes() );
            mvprintw( 2, 5, "O   : %d", left );
            mvprintw( t_ball->gety(), t_ball->getx(), "O" );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball ) override
        {
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

            auto end = std::chrono::steady_clock::now();

            if ( std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count() >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        int  duration{ 10 };
};

#endif
