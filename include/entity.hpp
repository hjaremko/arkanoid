#ifndef ENTITY_H
#define ENTITY_H

#include "point.hpp"

#include <curses.h>

class ball_state;

class entity
{
public:
    enum class color_pair
    {
        red = 1,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };

    entity() = default;
    virtual ~entity() = default;
    virtual void draw() const = 0;
    [[nodiscard]] virtual bool intersects( const point& t_point ) const = 0;
    [[nodiscard]] virtual bool is_destroyable() const;
    [[nodiscard]] virtual bool is_collideable() const;

    virtual void set_position( int t_y, int t_x );

    virtual void set_position( const point& t_pos );
    void set_color( color_pair t_color );
    void set_attributes( chtype t_attributes );
    void sety( int t_y );
    void setx( int t_x );

    virtual void set_width( int t_width );
    void set_height( int t_height );
    int gety() const;
    int getx() const;

    virtual int width() const;
    int height() const;
    int get_color() const;
    chtype get_attributes() const;
    point get_position() const;

protected:
    point m_position { 0, 0 };
    int m_width { 0 };
    int m_height { 0 };
    int m_color { 0 };
    chtype m_attributes { 0 };
};

#endif // ENTITY_H
