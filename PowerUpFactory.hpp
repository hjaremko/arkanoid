#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "PowerUp.hpp"
#include "BallPowerUp.hpp"
#include "PaddlePowerUp.hpp"

class PowerUpFactory
{
    public:
        static PowerUp* create( PowerUp::Type t_type, PowerUp::Power t_powerId )
        {
            if ( t_type == PowerUp::Type::Ball )
            {
                return new BallPowerUp( t_powerId );
            }
            else if ( t_type == PowerUp::Type::Paddle )
            {
                return new PaddlePowerUp( t_powerId );
            }
            else
            {
                return nullptr;
            }
        }

        static PowerUp* createRandom()
        {
            PowerUp::Power powerUpId = static_cast<PowerUp::Power>( rand() % PowerUp::Power::None );
            PowerUp* power = nullptr;

            switch ( powerUpId )
            {
                case PowerUp::Power::AllBreaking:
                case PowerUp::Power::Slow:
                {
                    power = create( PowerUp::Type::Ball, powerUpId );

                    break;
                }

                case PowerUp::Power::Shooter:
                case PowerUp::Power::Sticky:
                case PowerUp::Power::Enlarge:
                case PowerUp::Power::Shrink:
                {
                    power = create( PowerUp::Type::Paddle, powerUpId );

                    break;
                }

                case PowerUp::Power::None:
                    break;
            }

            return power;
        }

    protected:
        PowerUpFactory();
};

#endif
