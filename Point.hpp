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

        static bool isOut( const Point& t_point )
        {
            return t_point.gety() < 0 || t_point.gety() > getmaxy( stdscr ) - 1 || t_point.getx() < 0 || t_point.getx() > getmaxx( stdscr ) - 1;
        }
        
    private:

};

#endif //POINT_H
