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

        void setPosition( const int t_y, const int t_x )
        {
            m_position = Point( t_y, t_x );
        }

        void setPosition( const Point& t_pos )
        {
            m_position = t_pos;
        }

        void setColorPair( const ColorPair t_color )
        {
            m_color = static_cast<int>( t_color );
        }

        void setAttribiutes( const int t_attributes )
        {
            m_attributes = t_attributes;
        }

        auto getPosition() const
        {
            return m_position;
        }

        int gety() const
        {
            return m_position.y;
        }

        int getx() const
        {
            return m_position.x;
        }

        void sety( const int t_y )
        {
            m_position.y = t_y;
        }

        void setx( const int t_x )
        {
            m_position.x = t_x;
        }

        void setWidth( const int t_width )
        {
            m_width = t_width;
        }

        void setHeight( const int t_height )
        {
            m_height = t_height;
        }

        int getWidth() const
        {
            return m_width;
        }

        int getHeight() const
        {
            return m_height;
        }

        bool isDestroyable() const
        {
            return m_isDestroyable;
        }

        int getColor() const
        {
            return m_color;
        }

        int getAttributes() const
        {
            return m_attributes;
        }

    protected:
        Point m_position{ 0, 0 };
        int   m_width{ 0 };
        int   m_height{ 0 };
        int   m_color{ 0 };
        int   m_attributes{ 0 };
        bool  m_isDestroyable{ true };
};

#endif //ENTITY_H
