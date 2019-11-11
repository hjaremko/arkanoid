#ifndef POINT_H
#define POINT_H

#include <curses.h>

class point
{
    public:
        point() {};
        point( int t_y, int t_x ) : y( t_y ), x( t_x ) {}

        int getx() const
        {
            return x;
        }

        int gety() const
        {
            return y;
        }

        bool is_out()
        {
            return ( gety() <  0 || gety() > getmaxy( stdscr ) ||
                     getx() < -1 || getx() > getmaxx( stdscr ) );
        }

        point& operator+=( const point& rhs )
        {
            y += rhs.y;
            x += rhs.x;

            return *this;
        }

        int y{ 0 };
        int x{ 0 };
};

inline point operator+( point lhs, const point& rhs )
{
    lhs += rhs;
    return lhs;
}

#endif //POINT_H
