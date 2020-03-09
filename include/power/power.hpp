#ifndef POWERUP_H
#define POWERUP_H

#include "entity.hpp"
#include "system_clock.hpp"

namespace arkanoid
{
class map;
}

class power : public entity
{
public:
    power()
    {
        set_attributes( A_BOLD );
    }

    power( const power& ) = default;
    power( power&& ) = default;
    auto operator=( const power& ) -> power& = default;
    auto operator=( power && ) -> power& = default;
    ~power() override = default;

    virtual void apply( arkanoid::map& ) = 0;
    virtual void create_power() = 0;

    void draw() const override
    {
        attron( COLOR_PAIR( color_ ) | attributes_ );
        mvprintw( gety(), getx(), "%c", m_look );
        attrset( A_NORMAL );
    }

    void fall()
    {
        const auto current_tick = arkanoid::system_clock::ticks;
        if ( current_tick - last_tick_ >= 8 )
        {
            set_position( gety() + 1, getx() );
            last_tick_ = current_tick;
        }
    }

    [[nodiscard]] auto intersects( const point& t_point ) const -> bool override
    {
        return getx() == t_point.y && getx() == t_point.x;
    }

    [[nodiscard]] auto is_destroyable() const -> bool override
    {
        return false;
    }

    [[nodiscard]] auto can_collide() const -> bool override
    {
        return false;
    }

    char m_look { '%' };
    arkanoid::system_clock::ticks_type last_tick_ { 0 };
};

#endif
