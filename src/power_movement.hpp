#ifndef POWERUPMOVEMENT_H
#define POWERUPMOVEMENT_H

#include <mutex>

#include "power.hpp"

extern std::mutex m;

class power_movement
{
public:
    explicit power_movement( power* t_power ) : m_power( t_power )
    {
    }

    void operator()() const
    {
        while ( !map::instance()->get_paddle()->intersects( m_power->get_position() ) &&
                !m_power->get_position().is_out() )
        {
            m_power->set_position( m_power->gety() + 1, m_power->getx() );

            std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
        }

        if ( !m_power->get_position().is_out() )
        {
            std::lock_guard<std::mutex> lock( m );

            m_power->apply();
        }

        map::instance()->destroy( m_power );
    }

private:
    power* m_power{ nullptr };
};

#endif
