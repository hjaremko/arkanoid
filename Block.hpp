#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.hpp"
#include "Glyph.hpp"

class Block : public Entity
{
    public:
        Block();
        Block( ColorPair, chtype, const Point& );
        void draw() const;
        void destroy() const;

        bool intersects( const Point& t_point ) const
        {
            return  t_point.y >= gety() && t_point.y < ( gety() + getHeight() ) &&
                    t_point.x >= getx() && t_point.x < ( getx() + getWidth()  );
        }

    private:
        char m_look{ '#' };
};

#endif //BLOCK_H
