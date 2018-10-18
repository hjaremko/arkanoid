#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Map.hpp"
// #include "BallState.hpp"
// #include "PaddleState.hpp"

class PowerUp : public Entity
{
    public:
        PowerUp() {}
        ~PowerUp() {};

        enum class Type
        {
            Ball,
            Paddle,
            None
        };

        enum Power
        {
            AllBreaking,
            Slow,
            Shooter,
            // Sticky,
            StickyBall,
            Enlarge,
            Shrink,
            None
        };

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

        void setType( Type t_powerType )
        {
            m_type = t_powerType;
        }

        void setPower( Power t_powerType )
        {
            m_power = t_powerType;
        }

        char m_look{ '%' };
    protected:
        bool m_isDestroyable{ false };
        Power m_power{ Power::None };
        Type  m_type{ Type::None };
};

#endif
