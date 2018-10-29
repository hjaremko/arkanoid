#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "PowerUp.hpp"
#include "BallPowerUp.hpp"
#include "PaddlePowerUp.hpp"

int random( int min, int max );

class BallPowerUpFactory
{
    public:
        static PowerUp* create( BallPowerUp::Type t_type )
        {
            auto power = new BallPowerUp();
            power->setPower( t_type );

            switch ( t_type )
            {
                case BallPowerUp::Type::AllBreaking:
                    power->setColorPair( Entity::ColorPair::Red );

                    break;
                case BallPowerUp::Type::Slow:
                    power->setColorPair( Entity::ColorPair::Yellow );

                    break;
                case BallPowerUp::Type::Fast:
                    power->setColorPair( Entity::ColorPair::Magenta );

                    break;
                case BallPowerUp::Type::StickyBall:
                    power->setColorPair( Entity::ColorPair::Green );

                    break;
                case BallPowerUp::Type::Extra:
                    power->setColorPair( Entity::ColorPair::White );

                    break;
                case BallPowerUp::Type::None:
                    power = nullptr;

                    break;
            }

            return power;
        }

        static PowerUp* createRandom()
        {
            auto randomPowerId = random( BallPowerUp::Type::AllBreaking, BallPowerUp::Type::None - 1 );

            return create( static_cast<BallPowerUp::Type>( randomPowerId ) );
        }
};

class PaddlePowerUpFactory
{
    public:
        static PowerUp* create( PaddlePowerUp::Type t_type )
        {
            auto power = new PaddlePowerUp();
            power->setPower( t_type );

            switch ( t_type )
            {
                case PaddlePowerUp::Type::Shooter:
                    power->setColorPair( Entity::ColorPair::Cyan );

                    break;
                case PaddlePowerUp::Type::Barrier:
                    power->m_look = '~';
                    power->setColorPair( Entity::ColorPair::Green );

                    break;
                case PaddlePowerUp::Type::Enlarge:
                    power->m_look = '+';
                    power->setColorPair( Entity::ColorPair::Green );

                    break;
                case PaddlePowerUp::Type::Shrink:
                    power->m_look = '-';
                    power->setColorPair( Entity::ColorPair::Red );

                    break;
                case PaddlePowerUp::Type::None:
                    power = nullptr;

                    break;
            }

            return power;
        }

        static PowerUp* createRandom()
        {
            auto randomPowerId = random( PaddlePowerUp::Type::Shooter, PaddlePowerUp::Type::None - 1 );

            return create( static_cast<PaddlePowerUp::Type>( randomPowerId ) );
        }
};

class PowerUpFactory
{
    public:
        static PowerUp* createRandom()
        {
            PowerUp* power = nullptr;

            if ( random( 0, 1 ) )
            {
                return BallPowerUpFactory::createRandom();
            }
            else
            {
                return PaddlePowerUpFactory::createRandom();
            }

            return power;
        }

    protected:
        PowerUpFactory();
};

#endif
