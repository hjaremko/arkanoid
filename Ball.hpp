#ifndef BALL_H
#define BALL_H

#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <curses.h>

#include "Entity.hpp"
#include "Vector2D.hpp"

#define PI 3.14159265

class Ball : public Entity
{
    public:
        enum class ReflectionAxis
        {
            Horizontal,
            Vertical,
            None
        };

        Ball();
        Ball( std::vector<Entity*>* t_map ) : m_map( t_map ) {}

        void           draw() const;
        void           move( const int, const int );
        void           shoot();
        void           reflect( ReflectionAxis );
        void           destroy( Entity* t_entity );
        bool           isOut() const;
        bool           intersects( const Point& t_point ) const;
        Vector2D       getVelocity() const;
        ReflectionAxis intersects(); //const!!
        ReflectionAxis out() const;
    private:
        std::vector<Entity*>* m_map;
        Vector2D              m_velocity{ Vector2D( -1, 1 ) };
        char                  m_look{ 'O' };
        int                   m_speed{ 150 };
};

#endif //BALL_H
