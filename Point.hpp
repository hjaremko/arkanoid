#ifndef POINT_H
#define POINT_H

#include <curses.h>

class Point
{
    public:
        Point() {};
        Point( int t_y, int t_x ) : y( t_y ), x( t_x ) {}

        int y{ 0 };
        int x{ 0 };

        int getx() const
        {
            return x;
        }

        int gety() const
        {
            return y;
        }
};

#endif //POINT_H
