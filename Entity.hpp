#ifndef ENTITY_H
#define ENTITY_H

#include <curses.h>

#include "Point.hpp"

class BallState;

class Entity
{
    public:
        enum class ColorPair
        {
            Red = 1,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White
        };

        Entity() {}
        virtual ~Entity() {}
        virtual void draw() const = 0;
        virtual bool intersects( const Point& t_point ) const = 0;

        void  setPosition( const int t_y, const int t_x );
        void  setPosition( const Point& t_pos );
        void  setColorPair( const ColorPair t_color );
        void  setAttribiutes( const int t_attributes );
        void  sety( const int t_y );
        void  setx( const int t_x );
        void  setWidth( const int t_width );
        void  setHeight( const int t_height );
        int   gety() const;
        int   getx() const;
        int   getWidth() const;
        int   getHeight() const;
        int   getColor() const;
        int   getAttributes() const;
        bool  isDestroyable() const;
        bool  isCollidable() const;
        Point getPosition() const;

    protected:
        Point m_position{ 0, 0 };
        int   m_width{ 0 };
        int   m_height{ 0 };
        int   m_color{ 0 };
        int   m_attributes{ 0 };
        bool  m_isDestroyable{ true };
        bool  m_isCollidable{ true };
};

#endif //ENTITY_H
