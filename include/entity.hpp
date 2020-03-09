#ifndef ENTITY_H
#define ENTITY_H

#include "point.hpp"

#include <curses.h>

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
    entity( const entity& ) = default;
    entity( entity&& ) = default;
    auto operator=( const entity& ) -> entity& = default;
    auto operator=( entity && ) -> entity& = default;
    virtual ~entity() = default;

    virtual void draw() const = 0;
    [[maybe_unused]] [[nodiscard]] virtual auto intersects( const point& ) const
        -> bool = 0;
    [[nodiscard]] virtual auto is_destroyable() const -> bool;
    [[nodiscard]] virtual auto can_collide() const -> bool;

    virtual void set_position( int, int );
    virtual void set_position( const point& );
    void set_color( color_pair );
    void set_attributes( chtype );
    void sety( int );
    void setx( int );

    virtual void set_width( int );
    [[nodiscard]] virtual auto width() const -> int;

    void set_height( int );
    [[nodiscard]] auto gety() const -> int;
    [[nodiscard]] auto getx() const -> int;
    [[nodiscard]] auto height() const -> int;
    [[nodiscard]] auto get_color() const -> int;
    [[nodiscard]] auto get_attributes() const -> chtype;
    [[nodiscard]] auto get_position() const -> point;

protected:
    point position_ { 0, 0 };
    int width_ { 0 };
    int height_ { 0 };

    int color_ { 0 };
    chtype attributes_ { 0 };
};

#endif // ENTITY_H
