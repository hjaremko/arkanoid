#ifndef ARKANOID_UNBREAKABLE_BLOCK_HPP
#define ARKANOID_UNBREAKABLE_BLOCK_HPP

#include "block.hpp"

class unbreakable_block : public block
{
public:
    unbreakable_block( color_pair color,
                       chtype attributes,
                       const point& point = { 0, 0 } )

        : block( color, attributes, point )
    {
        set_look( 'X' );
    }

    [[nodiscard]] auto is_destroyable() const -> bool override
    {
        return false;
    }
};

#endif // ARKANOID_UNBREAKABLE_BLOCK_HPP
