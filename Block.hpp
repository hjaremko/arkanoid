#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <curses.h>

#include "Entity.hpp"

class Block : public Entity
{
    public:
        Block();
        Block( ColorPair, chtype, const Point& );
        void draw() const override;
        void destroy() const;

        bool intersects( const Point& t_point ) const override
        {
            return  t_point.y >= gety() && t_point.y < ( gety() + getHeight() ) &&
                    t_point.x >= getx() && t_point.x < ( getx() + getWidth()  );
        }

    private:
        char m_look{ '#' };
};

class UnbreakableBlock : public Block
{
    public:
        UnbreakableBlock( ColorPair t_color, chtype t_attributes, const Point& t_point = Point( 0, 0 ) )
        {
            setColorPair( t_color );
            setAttribiutes( t_attributes );
            Entity::setPosition( t_point );
        }

        bool isDestroyable() const
        {
            return false;
        }
};

#endif //BLOCK_H
