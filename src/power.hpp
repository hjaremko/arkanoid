#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <cstdlib>
#include <ctime>

#include "entity.hpp"
#include "map.hpp"

class power : public entity
{
public:
    power()
    {
        set_attributes( A_BOLD );
    }

    ~power() override = default;
    virtual void apply() = 0;
    virtual void createPower() = 0;

    void draw() const override
    {
        attron( COLOR_PAIR( m_color ) | m_attributes );
        mvprintw( gety(), getx(), "%c", m_look );
        attrset( A_NORMAL );
    }

    bool intersects( const point& t_point ) const override
    {
        return getx() == t_point.y && getx() == t_point.x;
    }

    bool is_destroyable() const override
    {
        return false;
    }

    bool is_collideable() const override
    {
        return false;
    }

    char m_look{ '%' };
};

#endif
