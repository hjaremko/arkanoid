#ifndef POWERUPMOVEMENT_H
#define POWERUPMOVEMENT_H

#include "PowerUp.hpp"

class PowerUpMovement
{
    public:
        explicit PowerUpMovement( PowerUp* t_power ) : m_power( t_power ) {}

        void operator()() const
        {
            while ( !Map::instance()->getPaddle()->intersects( m_power->getPosition() ) ) //out
            {
                m_power->setPosition( m_power->gety() + 1, m_power->getx() );
                std::this_thread::sleep_for(
                    std::chrono::milliseconds( 200 ) );
            }

            m_power->apply();
            Map::instance()->destroy( m_power );
        }

    private:
        PowerUp* m_power{ nullptr };
};

#endif
