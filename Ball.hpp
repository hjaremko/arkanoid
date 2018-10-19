#ifndef BALL_H
#define BALL_H

#include <vector>
#include <curses.h>

#include "Entity.hpp"
#include "Point.hpp"

// #define PI 3.14159265

class BallState;

class Ball : public Entity
{
    public:
        enum ReflectionAxis
        {
            Horizontal = 1,
            Vertical = 2,
            Backwards = 3,
            None = 0
        };

        Ball();

        void           draw() const override;
        void           moveBy( const int, const int );
        void           moveBy( const Point& );
        void           shoot();
        void           reflect( ReflectionAxis );
        void           setVelocity( const Point& );
        void           setVectorY( int );
        void           setVectorX( int );
        void           setSpeed( const int );
        void           changeSpeedBy( const int );
        void           changeState( BallState* );
        void           setStopped( const bool );
        bool           isStopped() const;
        bool           isOut() const;
        bool           isNull() const;
        bool           intersects( const Point& ) const override;
        char           getLook() const;
        int            getSpeed() const;
        Point          getVelocity() const;
        ReflectionAxis getWallReflectionAxis() const;
        ReflectionAxis getReflectionAxis( Entity* ) const;
        BallState*     getState() const;
        Entity*        collides() const;

        static const int MIN_SPEED{ 30 };
        static const int DEF_SPEED{ 80 };
    private:
        friend class BallState;
        friend class BallNormal;
        friend class BallAllBreaking;
        friend class BallBullet;

        BallState* m_state{ nullptr };
        Point      m_velocity{ Point( -1, 1 ) };
        char       m_look{ 'O' };
        int        m_speed{ DEF_SPEED };
        bool       m_stopped{ true };
};

#endif //BALL_H
