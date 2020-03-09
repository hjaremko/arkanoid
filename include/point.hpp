#ifndef POINT_H
#define POINT_H

#include <curses.h>

class point
{
public:
    point() = default;
    point( int _y, int _x ) : y( _y ), x( _x )
    {
    }

    // TODO: get<>
    [[nodiscard]] auto getx() const -> int
    {
        return x;
    }

    [[nodiscard]] auto gety() const -> int
    {
        return y;
    }

    auto is_out() -> bool
    {
        return ( gety() < 0 || gety() > getmaxy( stdscr ) || getx() < -1 ||
                 getx() > getmaxx( stdscr ) );
    }

    auto operator+=( const point& rhs ) -> point&
    {
        y += rhs.y;
        x += rhs.x;

        return *this;
    }

    int y { 0 };
    int x { 0 };
};

inline auto operator+( point lhs, const point& rhs ) -> point
{
    lhs += rhs;
    return lhs;
}

#endif // POINT_H
