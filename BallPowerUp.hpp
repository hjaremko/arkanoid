#ifndef BALLPOWERUP_H
#define BALLPOWERUP_H

#include "PowerUp.hpp"
#include "BallAllBreaking.hpp"
#include "BallSlow.hpp"
#include "BallSticky.hpp"

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
                case Power::Extra:
                    setColorPair( Entity::ColorPair::White );

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
            if ( m_power == Power::Extra )
            {
                auto ball = Map::instance()->newBall();
                ball->setPosition( Map::instance()->getBalls().front()->getPosition() );
                Map::instance()->getPaddle()->getBall( ball );  //
                Map::instance()->getPaddle()->shoot();          //!
            }
            else
            {
                createPower();

                for ( auto& ball : Map::instance()->getBalls() )
                {
                    ball->changeState( m_state );
                }
            }
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
                case Power::Extra:
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
