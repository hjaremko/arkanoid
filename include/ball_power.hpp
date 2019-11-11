#ifndef BALLPOWERUP_H
#define BALLPOWERUP_H

#include "ball_allbreaking.hpp"
#include "ball_fast.hpp"
#include "ball_slow.hpp"
#include "ball_sticky.hpp"
#include "ball_weird.hpp"
#include "power.hpp"

class ball_power : public power
{
public:
    ball_power() = default;

    enum type
    {
        allbreaking,
        slow,
        fast,
        extra,
        sticky,
        weird,
        none
    };

    void setPower( type t_powerType )
    {
        m_power = t_powerType;
    }

    void apply() override
    {
        if ( m_power == extra )
        {
            auto ball = map::instance()->new_ball();
            ball->set_position( map::instance()->get_balls().front()->get_position() );
            map::instance()->get_paddle()->get_ball( ball ); //
            map::instance()->get_paddle()->shoot();          //!
        }
        else
        {
            create_power();

            for ( auto& ball : map::instance()->get_balls() )
            {
                ball->set_state( m_state );
            }
        }
    }

    void create_power() override
    {
        switch ( m_power )
        {
        case allbreaking:
            m_state = new ball_allbreaking;

            break;
        case slow:
            m_state = new ball_slow;

            break;
        case fast:
            m_state = new ball_fast;

            break;
        case sticky:
            m_state = new ball_sticky;

            break;
        case weird:
            m_state = new ball_weird;

            break;
        case extra:
        case none:
            break;
        }
    }

private:
    ball_state* m_state { nullptr };
    type m_power { type::none };
};

#endif
