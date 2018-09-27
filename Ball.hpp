#ifndef BALL_H
#define BALL_H

#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <curses.h>

#include "Entity.hpp"
#include "Point.hpp"
#include "Vector2D.hpp"

#define PI 3.14159265

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
        Ball( std::vector<Entity*>* );

        void           draw() const;
        void           moveBy( const int, const int );
        void           shoot();
        void           reflect( ReflectionAxis );
        void           destroy( Entity* );
        void           setVelocity( Vector2D& );
        void           setVectorY( int );
        void           setVectorX( int );
        void           setSpeed( const int );
        void           changeSpeedBy( const int );
        bool           isOut() const;
        bool           intersects( const Point& ) const;
        char           getLook() const;
        int            getSpeed() const;
        Vector2D       getVelocity() const;
        ReflectionAxis intersects(); //const!!
        ReflectionAxis out() const;
        void changeState( BallState* );

        static const int MIN_SPEED{ 40 };
    private:
        friend class BallState;
        friend class BallNormal;
        friend class BallAllBreaking;

        std::vector<Entity*>* m_map;
        BallState*            m_state;
        Vector2D              m_velocity{ Vector2D( -1, 1 ) };
        char                  m_look{ 'O' };
        int                   m_speed{ 130 };
};

#endif //BALL_H
