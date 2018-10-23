#ifndef POWERUPMOVEMENT_H
#define POWERUPMOVEMENT_H

#include <mutex>

#include "PowerUp.hpp"

extern std::mutex m;

class PowerUpMovement
{
    public:
        explicit PowerUpMovement( PowerUp* t_power ) : m_power( t_power ) {}

        void operator()() const
        {
            while ( !Map::instance()->getPaddle()->intersects( m_power->getPosition() ) &&
                    !m_power->getPosition().isOut() )
            {
                m_power->setPosition( m_power->gety() + 1, m_power->getx() );

                std::this_thread::sleep_for(
                    std::chrono::milliseconds( 200 ) );
            }

            if ( !m_power->getPosition().isOut() )
            {
                std::lock_guard<std::mutex> lock( m );

                m_power->apply();
            }

            Map::instance()->destroy( m_power );
        }

    private:
        PowerUp* m_power{ nullptr };
};

#endif
