#ifndef BLOCK_H
#define BLOCK_H

#include "entity.hpp"

#include <vector>

class block : public entity
{
public:
    block() = default;
    block( color_pair, chtype, const point& );
    void draw() const override;
    void set_look( char );

    [[nodiscard]] auto intersects( const ::point& point ) const -> bool override
    {
        return point.y >= gety() && point.y < ( gety() + height() ) &&
               point.x >= getx() && point.x < ( getx() + width() );
    }

private:
    char look_ { '#' };
};

#endif // BLOCK_H
