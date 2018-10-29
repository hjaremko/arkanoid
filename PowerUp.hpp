#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Map.hpp"

class PowerUp : public Entity
{
    public:
        PowerUp()
        {
            setAttribiutes( A_BOLD );
        }

        ~PowerUp() {};

        virtual void apply() = 0;
        virtual void createPower() = 0;

        void draw() const
        {
            attron( COLOR_PAIR( m_color ) | m_attributes );
            mvprintw( gety(), getx(), "%c", m_look );
            attrset( A_NORMAL );
        }

        bool intersects( const Point& t_point ) const
        {
            return getx() == t_point.y && getx() == t_point.x;
        }

        bool isDestroyable() const override
        {
            return false;
        }

        bool isCollidable() const override
        {
            return false;
        }

        char m_look{ '%' };
    protected:
};

#endif
