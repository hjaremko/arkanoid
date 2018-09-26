#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
    Vector2D() {}
    Vector2D( const int t_y, const int t_x ) : y( t_y ), x( t_x ) {}

    void sety( int t_y )
    {
        y = t_y;
    }

    void setx( int t_x )
    {
        x = t_x;
    }

    int y{ 0 };
    int x{ 0 };
};

#endif
