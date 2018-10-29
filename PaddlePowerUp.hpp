#ifndef PADDLEPOWERUP_H
#define PADDLEPOWERUP_H

#include "PowerUp.hpp"
#include "PaddleShooter.hpp"
#include "PaddleBarrier.hpp"

class PaddlePowerUp : public PowerUp
{
    public:
        PaddlePowerUp()
        {
        }

        enum Type
        {
            Shooter,
            Enlarge,
            Shrink,
            Barrier,
            None
        };

        void setPower( Type t_powerType )
        {
            m_power = t_powerType;
        }

        void apply() override
        {
            if ( m_power == Enlarge )
            {
                Map::instance()->getPaddle()->changeSizeBy( 4 );
            }
            else if ( m_power == Shrink )
            {
                Map::instance()->getPaddle()->changeSizeBy( -4 );
            }
            else
            {
                createPower();
                Map::instance()->getPaddle()->changeState( m_state );
            }
        }

        void createPower() override
        {
            switch ( m_power ) 
            {
                case Shooter:
                    m_state = new PaddleShooter;

                    break;
                case Barrier:
                    m_state = new PaddleBarrier;

                    break;
                default:
                    break;
            }
        }

    private:
        PaddleState* m_state{ nullptr };
        Type m_power{ Type::None };
};

#endif
