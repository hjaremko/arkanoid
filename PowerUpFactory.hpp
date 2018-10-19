#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "PowerUp.hpp"
#include "BallPowerUp.hpp"
#include "PaddlePowerUp.hpp"

int random( int min, int max );

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
            auto powerUpId = random( PowerUp::Power::AllBreaking, PowerUp::Power::None - 1 );
            PowerUp::Power randomPower = static_cast<PowerUp::Power>( powerUpId );
            PowerUp* power = nullptr;

            switch ( randomPower )
            {
                case PowerUp::Power::AllBreaking:
                case PowerUp::Power::Slow:
                case PowerUp::Power::StickyBall:
                {
                    power = create( PowerUp::Type::Ball, randomPower );

                    break;
                }

                case PowerUp::Power::Shooter:
                // case PowerUp::Power::Sticky:
                case PowerUp::Power::Enlarge:
                case PowerUp::Power::Shrink:
                {
                    power = create( PowerUp::Type::Paddle, randomPower );

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
