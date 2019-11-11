#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "ball_power.hpp"
#include "paddle_power.hpp"
#include "power.hpp"

class ball_power_factory
{
public:
    static power* create( ball_power::type t_type )
    {
        auto power = new ball_power();
        power->setPower( t_type );

        switch ( t_type )
        {
        case ball_power::type::allbreaking:
            power->set_color( entity::color_pair::red );

            break;
        case ball_power::type::slow:
            power->set_color( entity::color_pair::yellow );

            break;
        case ball_power::type::fast:
            power->set_color( entity::color_pair::magenta );

            break;
        case ball_power::type::sticky:
            power->set_color( entity::color_pair::green );

            break;
        case ball_power::type::extra:
            power->set_color( entity::color_pair::white );

            break;
        case ball_power::type::weird:
            power->set_color( entity::color_pair::cyan );

            break;
        case ball_power::type::none:
            power = nullptr;

            break;
        }

        return power;
    }

    static power* create_random()
    {
        auto random_power_id = random( ball_power::type::allbreaking, ball_power::type::none - 1 );

        return create( static_cast<ball_power::type>( random_power_id ) );
    }
};

class paddle_power_factory
{
public:
    static power* create( paddle_power::type t_type )
    {
        auto power = new paddle_power();
        power->set_power( t_type );

        switch ( t_type )
        {
        case paddle_power::type::shooter:
            power->m_look = '^';
            power->set_color( entity::color_pair::cyan );

            break;
        case paddle_power::type::barrier:
            power->m_look = '~';
            power->set_color( entity::color_pair::green );

            break;
        case paddle_power::type::enlarge:
            power->m_look = '+';
            power->set_color( entity::color_pair::green );

            break;
        case paddle_power::type::shrink:
            power->m_look = '-';
            power->set_color( entity::color_pair::red );

            break;
        case paddle_power::type::none:
            power = nullptr;

            break;
        }

        return power;
    }

    static power* createRandom()
    {
        auto random_power_id = random( paddle_power::type::shooter, paddle_power::type::none - 1 );

        return create( static_cast<paddle_power::type>( random_power_id ) );
    }
};

class power_factory
{
public:
    static power* create_random()
    {
        if ( random( 0, 1 ) )
        {
            return ball_power_factory::create_random();
        }
        else
        {
            return paddle_power_factory::createRandom();
        }
    }

protected:
    power_factory() = default;
};

#endif
