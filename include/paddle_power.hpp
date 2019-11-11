#ifndef PADDLEPOWERUP_H
#define PADDLEPOWERUP_H

#include "paddle_barrier.hpp"
#include "paddle_shooter.hpp"
#include "power.hpp"

class paddle_power : public power
{
public:
    paddle_power()
    {
    }

    enum type
    {
        shooter,
        enlarge,
        shrink,
        barrier,
        none
    };

    void set_power( type t_powerType )
    {
        m_power = t_powerType;
    }

    void apply() override
    {
        if ( m_power == enlarge )
        {
            map::instance()->get_paddle()->change_size_by( 4 );
        }
        else if ( m_power == shrink )
        {
            map::instance()->get_paddle()->change_size_by( -4 );
        }
        else
        {
            create_power();
            map::instance()->get_paddle()->set_state( m_state );
        }
    }

    void create_power() override
    {
        switch ( m_power )
        {
        case shooter:
            m_state = new paddle_shooter;

            break;
        case barrier:
            m_state = new paddle_barrier;

            break;
        default:
            break;
        }
    }

private:
    paddle_state* m_state { nullptr };
    type m_power { type::none };
};

#endif
