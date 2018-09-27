#ifndef BALLSTATE_H
#define BALLSTATE_H

#include <chrono>

#include "Ball.hpp"
#include "Paddle.hpp"

class BallState
{
    public:
        virtual ~BallState() {}

        virtual void draw( const Ball* );
        virtual void shoot( Ball* );
        virtual void reflect( Ball*, Ball::ReflectionAxis );
        virtual Ball::ReflectionAxis intersects( Ball* );
};

class BallNormal : public BallState
{
    public:
        void draw( const Ball* t_ball )
        {
            attron( COLOR_PAIR( t_ball->getColor() ) | t_ball->getAttributes() );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );
            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball )
        {
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( t_ball->getSpeed() ) );
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis )
        {
            if ( t_axis == Ball::ReflectionAxis::Vertical )
            {
                t_ball->setVectorY( -t_ball->getVelocity().y );
            }
            else if ( t_axis == Ball::ReflectionAxis::Horizontal )
            {
                t_ball->setVectorX( -t_ball->getVelocity().x );
            }

            if ( t_ball->getSpeed() > Ball::MIN_SPEED && t_axis != Ball::ReflectionAxis::None )
            {
                t_ball->changeSpeedBy( -2 );
            }
        }

        Ball::ReflectionAxis intersects( Ball* t_ball )
        {
            Ball::ReflectionAxis axis = Ball::ReflectionAxis::None;

            for ( auto& entity : *t_ball->m_map )
            {
                if ( entity->intersects( Point( t_ball->gety() + t_ball->getVelocity().y,
                                                t_ball->getx() + t_ball->getVelocity().x ) ) )
                {
                    if ( ( t_ball->getx()                           <  entity->getx()    &&
                           t_ball->getx() + t_ball->getVelocity().x >= entity->getx() )  ||
                         ( t_ball->getx()                           >  entity->getx() + entity->getWidth() - 1     &&
                           t_ball->getx() + t_ball->getVelocity().x <= entity->getx() + entity->getWidth() - 1 ) )
                    {
                        axis = Ball::ReflectionAxis::Horizontal;
                    }

                    if ( ( t_ball->gety()                           <  entity->gety()    &&
                           t_ball->gety() + t_ball->getVelocity().y >= entity->gety() )  ||
                         ( t_ball->gety()                           >  entity->gety() + entity->getHeight() - 1    &&
                           t_ball->gety() + t_ball->getVelocity().y <= entity->gety() + entity->getHeight() - 1 ) )
                    {
                        axis = Ball::ReflectionAxis::Vertical;
                    }

                    if ( entity->isDestroyable() )
                    {
                        t_ball->destroy( entity );
                    }
                }
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

        void draw( const Ball* t_ball )
        {
            attron( COLOR_PAIR( Entity::ColorPair::Red ) | t_ball->getAttributes() | A_BOLD );

            mvprintw( lastPosition.gety(), lastPosition.getx(), "*" );
            mvprintw( t_ball->gety(), t_ball->getx(), "%c", t_ball->getLook() );

            attrset( A_NORMAL );
        }

        void shoot( Ball* t_ball )
        {
            lastPosition = t_ball->getPosition();
            t_ball->moveBy( t_ball->getVelocity().y, t_ball->getVelocity().x );
            std::this_thread::sleep_for( std::chrono::milliseconds( t_ball->getSpeed() - 50 ) );

            auto end = std::chrono::steady_clock::now();

            if ( std::chrono::duration_cast<std::chrono::seconds>( end - startTimePoint ).count() >= duration )
            {
                t_ball->changeState( new BallNormal );
            }
        }

        void reflect( Ball* t_ball, Ball::ReflectionAxis t_axis )
        {
            if ( t_axis == Ball::ReflectionAxis::Vertical )
            {
                t_ball->setVectorY( -t_ball->getVelocity().y );
            }
            else if ( t_axis == Ball::ReflectionAxis::Horizontal )
            {
                t_ball->setVectorX( -t_ball->getVelocity().x );
            }

            if ( t_ball->getSpeed() > Ball::MIN_SPEED && t_axis != Ball::ReflectionAxis::None )
            {
                t_ball->changeSpeedBy( -5 );
            }
        }

        Ball::ReflectionAxis intersects( Ball* t_ball )
        {
            Ball::ReflectionAxis axis = Ball::ReflectionAxis::None;

            for ( auto& entity : *t_ball->m_map )
            {
                if ( entity->intersects( Point( t_ball->gety() + t_ball->getVelocity().y,
                                                t_ball->getx() + t_ball->getVelocity().x ) ) )
                {
                    if ( entity->isDestroyable() )
                    {
                        t_ball->destroy( entity );
                    }
                    else if ( dynamic_cast<Paddle*>( entity ) )
                    {
                        axis = Ball::ReflectionAxis::Vertical;
                    }
                }
            }

            return axis;
        }

    private:
        std::chrono::steady_clock::time_point startTimePoint;
        Point lastPosition;
        int duration{ 10 };
};

#endif
