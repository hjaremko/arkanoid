#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "ball/ball_power.hpp"
#include "game_manager.hpp"
#include "paddle/paddle_power.hpp"
#include "power.hpp"

using power_ptr = std::unique_ptr<power>;

class ball_power_factory
{
public:
    static auto create( ball_power::type t_type ) -> power_ptr
    {
        auto power { std::make_unique<ball_power>() };
        power->set_power( t_type );

        switch ( t_type )
        {
        case ball_power::type::all_breaking:
            power->set_color( entity::color_pair::red );
            break;
        case ball_power::type::slow:
            power->set_color( entity::color_pair::cyan );
            break;
        case ball_power::type::fast:
            power->set_color( entity::color_pair::magenta );
            break;
        case ball_power::type::extra:
            power->set_color( entity::color_pair::white );
            break;
        case ball_power::type::weird:
            power->set_color( entity::color_pair::yellow );
            break;
        case ball_power::type::none:
            break;
        }

        return power;
    }

    static auto create_random() -> power_ptr
    {
        const auto random_power_id = arkanoid::game_manager::random(
            ball_power::type::all_breaking, ball_power::type::none - 1 );

        return create( static_cast<ball_power::type>( random_power_id ) );
    }
};

class paddle_power_factory
{
public:
    static auto create( paddle_power::type t_type ) -> power_ptr
    {
        auto power = std::make_unique<paddle_power>();
        power->set_power( t_type );

        switch ( t_type )
        {
        case paddle_power::type::shooter:
            power->m_look = '^';
            power->set_color( entity::color_pair::cyan );
            break;
        case paddle_power::type::barrier:
            power->m_look = '=';
            power->set_color( entity::color_pair::blue );
            break;
        case paddle_power::type::enlarge:
            power->m_look = '+';
            power->set_color( entity::color_pair::green );
            break;
        case paddle_power::type::shrink:
            power->m_look = '-';
            power->set_color( entity::color_pair::red );
            break;
        case paddle_power::type::sticky:
            power->m_look = '~';
            power->set_color( entity::color_pair::green );
            break;
        case paddle_power::type::none:
            break;
        }

        return power;
    }

    static auto create_random() -> power_ptr
    {
        auto random_power_id = arkanoid::game_manager::random(
            paddle_power::type::shooter, paddle_power::type::none - 1 );

        return create( static_cast<paddle_power::type>( random_power_id ) );
    }
};

class power_factory
{
public:
    static auto create_random() -> power_ptr
    {
        if ( arkanoid::game_manager::random( 0, 1 ) != 0 )
        {
            return ball_power_factory::create_random();
        }

        return paddle_power_factory::create_random();
    }

protected:
    power_factory() = default;
};

#endif
