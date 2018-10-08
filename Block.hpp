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

#endif //BLOCK_H
