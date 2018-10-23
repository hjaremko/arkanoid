#ifndef PADDLEPOWERUP_H
#define PADDLEPOWERUP_H

#include "PowerUp.hpp"
#include "PaddleShooter.hpp"

class PaddlePowerUp : public PowerUp
{
    public:
        PaddlePowerUp( PowerUp::Power t_power )
        {
            m_power = t_power;
            setAttribiutes( A_BOLD );

            switch ( m_power )
            {
                case Power::Shooter:
                    setColorPair( Entity::ColorPair::Cyan );

                    break;
                // case Power::Sticky:
                    // setColorPair( Entity::ColorPair::Green );

                    break;
                case Power::Enlarge:
                    m_look = '+';
                    setColorPair( Entity::ColorPair::Green );

                    break;
                case Power::Shrink:
                    m_look = '-';
                    setColorPair( Entity::ColorPair::Red );

                    break;
                case Power::Extra:
                case Power::StickyBall:
                case Power::AllBreaking:
                case Power::Slow:
                case Power::None:
                    break;
            }
        }

        void apply() override
        {
            if ( m_power == Power::Enlarge )
            {
                Map::instance()->getPaddle()->changeSizeBy( 4 );
            }
            else if ( m_power == Power::Shrink )
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
                case Power::Shooter:
                    m_state = new PaddleShooter;

                    break;
                // case Power::Sticky:
                    // m_state = new PaddleSticky;

                    // break;
                case Power::Extra:
                case Power::StickyBall:
                case Power::Enlarge:
                case Power::Shrink:
                case Power::AllBreaking:
                case Power::Slow:
                case Power::None:
                    break;
            }
        }

    private:
        PaddleState* m_state{ nullptr };
};

#endif
