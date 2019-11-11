#ifndef BALL_H
#define BALL_H

#include <vector>
#include <curses.h>

#include "entity.hpp"
#include "point.hpp"

// #define PI 3.14159265

class ball_state;

class ball : public entity
{
    public:
        enum reflection_axis
        {
            horizontal = 1,
            vertical = 2,
            backwards = 3,
            none = 0
        };

        ball();

        void           draw() const override;
        void           move_by( int, int );
        void           move_by( const point& );
        void           shoot();
        void           reflect( reflection_axis );
        void           set_velocity( const point& );
        void           set_vectorY( int );
        void           set_vectorX( int );
        void           set_speed( int );
        void           change_speed_by( int );
        void           set_state( ball_state* );
        void           set_stopped( bool );
        bool           is_stopped() const;
        bool           intersects( const point& ) const override;
        char           get_look() const;
        int            get_speed() const;
        point          get_velocity() const;
        reflection_axis get_wall_reflection_axis() const;
        reflection_axis get_reflection_axis( entity* ) const;
        ball_state*     get_state() const;
        entity*         collides() const;

        static const int MIN_SPEED{ 30 };
        static const int DEF_SPEED{ 80 };
    private:
        friend class ball_state;
        friend class BallNormal;
        friend class BallAllBreaking;
        friend class BallBullet;

        ball_state* m_state{ nullptr };
        point      m_velocity{ point( -1, 1 ) };
        char       m_look{ 'O' };
        int        m_speed{ DEF_SPEED };
        bool       m_stopped{ true };
};

#endif //BALL_H
