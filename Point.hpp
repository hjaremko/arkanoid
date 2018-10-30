#ifndef POINT_H
#define POINT_H

#include <curses.h>

class Point
{
    public:
        Point() {};
        Point( int t_y, int t_x ) : y( t_y ), x( t_x ) {}

        int getx() const
        {
            return x;
        }

        int gety() const
        {
            return y;
        }

        bool isOut()
        {
            return ( gety() <  0 || gety() > getmaxy( stdscr ) ||
                     getx() < -1 || getx() > getmaxx( stdscr ) );
        }

        Point& operator+=( const Point& rhs )
        {
            y += rhs.y;
            x += rhs.x;

            return *this;
        }

        int y{ 0 };
        int x{ 0 };
};

inline Point operator+( Point lhs, const Point& rhs )
{
    lhs += rhs;
    return lhs;
}

#endif //POINT_H
