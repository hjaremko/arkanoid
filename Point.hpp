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
            return ( gety() < 0 || gety() > getmaxy( stdscr ) - 1 ||
                     getx() < 0 || getx() > getmaxx( stdscr ) - 1 );
        }

        Point operator+( const Point& t_right ) const
        {
            return Point( y + t_right.y, x + t_right.x );
        }

        int y{ 0 };
        int x{ 0 };
};

#endif //POINT_H
