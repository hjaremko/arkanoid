#ifndef BALLPOWERUP_H
#define BALLPOWERUP_H

#include "PowerUp.hpp"

class BallPowerUp : public PowerUp
{
    public:
        BallPowerUp( PowerUp::Power t_power )
        {
            m_power = t_power;
            setAttribiutes( A_BOLD );

            switch ( m_power )
            {
                case Power::AllBreaking:
                    setColorPair( Entity::ColorPair::Red );

                    break;
                case Power::Slow:
                    setColorPair( Entity::ColorPair::Yellow );

                    break;
                case Power::StickyBall:
                    setColorPair( Entity::ColorPair::Green );

                    break;
                case Power::Shooter:
                // case Power::Sticky:
                case Power::Enlarge:
                case Power::Shrink:
                case Power::None:
                    break;
            }
        }

        void apply() override
        {
            createPower();
            Map::instance()->getBall( 0 )->changeState( m_state );
        }

        void createPower() override
        {
            switch ( m_power )
            {
                case Power::AllBreaking:
                    m_state = new BallAllBreaking;

                    break;
                case Power::Slow:
                    m_state = new BallSlow;

                    break;
                case Power::StickyBall:
                    m_state = new BallSticky;

                    break;
                case Power::Shooter:
                // case Power::Sticky:
                case Power::Enlarge:
                case Power::Shrink:
                case Power::None:
                    break;
            }
        }

    private:
        BallState* m_state{ nullptr };
};

#endif
