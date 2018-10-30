#ifndef BALLPOWERUP_H
#define BALLPOWERUP_H

#include "PowerUp.hpp"
#include "BallAllBreaking.hpp"
#include "BallSlow.hpp"
#include "BallFast.hpp"
#include "BallSticky.hpp"
#include "BallWeird.hpp"

class BallPowerUp : public PowerUp
{
    public:
        BallPowerUp()
        {
        }

        enum Type
        {
            AllBreaking,
            Slow,
            Fast,
            Extra,
            Sticky,
            Weird,
            None
        };

        void setPower( Type t_powerType )
        {
            m_power = t_powerType;
        }

        void apply() override
        {
            if ( m_power == Extra )
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
                case AllBreaking:
                    m_state = new BallAllBreaking;

                    break;
                case Slow:
                    m_state = new BallSlow;

                    break;
                case Fast:
                    m_state = new BallFast;

                    break;
                case Sticky:
                    m_state = new BallSticky;

                    break;
                case Weird:
                    m_state = new BallWeird;

                    break;
                case Extra:
                case None:
                    break;
            }
        }

    private:
        BallState* m_state{ nullptr };
        Type m_power{ Type::None };
};

#endif
