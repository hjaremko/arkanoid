#ifndef BALLPOWERUP_H
#define BALLPOWERUP_H

#include "ball_allbreaking.hpp"
#include "ball_fast.hpp"
#include "ball_slow.hpp"
#include "ball_weird.hpp"
#include "power/power.hpp"

class ball_power : public power
{
public:
    ball_power() = default;

    enum type
    {
        all_breaking,
        slow,
        fast,
        extra,
        weird,
        none
    };

    void set_power( type power_type )
    {
        power_type_ = power_type;
        create_power();
    }

    void apply( arkanoid::map& map ) override
    {
        if ( power_type_ == extra )
        {
            auto ball = std::make_unique<::ball>();
            ball->set_stopped( false );
            ball->set_position( ( *map.get_balls().begin() )->get_position() );
            map.get_balls().insert( std::move( ball ) );
            return;
        }

        for ( auto& ball : map.get_balls() )
        {
            ball->set_state( state_ );
        }
    }

    void create_power() override
    {
        switch ( power_type_ )
        {
        case all_breaking:
            state_ = std::make_shared<ball_allbreaking>();
            break;
        case slow:
            state_ = std::make_shared<ball_slow>();
            break;
        case fast:
            state_ = std::make_shared<ball_fast>();
            break;
        case weird:
            state_ = std::make_shared<ball_weird>();
            break;
        case extra:
        case none:
            break;
        }
    }

private:
    ball::state_ptr state_;
    type power_type_ { type::none };
};

#endif
