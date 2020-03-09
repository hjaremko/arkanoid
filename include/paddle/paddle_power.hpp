#ifndef PADDLEPOWERUP_H
#define PADDLEPOWERUP_H

#include "paddle_barrier.hpp"
#include "paddle_shooter.hpp"
#include "paddle_sticky.hpp"
#include "power/power.hpp"

class paddle_power : public power
{
public:
    enum type
    {
        shooter,
        enlarge,
        shrink,
        barrier,
        sticky,
        none
    };

    void set_power( type power_type )
    {
        power_type_ = power_type;
    }

    void apply( arkanoid::map& map ) override
    {
        if ( power_type_ == enlarge )
        {
            map.get_paddle()->change_size_by( 4 );
        }
        else if ( power_type_ == shrink )
        {
            map.get_paddle()->change_size_by( -4 );
        }
        else
        {
            create_power();
            map.get_paddle()->set_state( state_ );
        }
    }

    void create_power() override
    {
        switch ( power_type_ )
        {
        case shooter:
            state_ = std::make_shared<paddle_shooter>();
            break;
        case barrier:
            state_ = std::make_shared<paddle_barrier>();
            break;
        case sticky:
            state_ = std::make_shared<paddle_sticky>();
            break;
        default:
            break;
        }
    }

private:
    paddle::state_ptr state_;
    type power_type_ { type::none };
};

#endif
