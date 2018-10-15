#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Map.hpp"
#include "BallState.hpp"
#include "PaddleState.hpp"

class PowerUp : public Entity
{
    public:
        PowerUp() {}
        ~PowerUp() {};

        enum class Type
        {
            Ball,
            Paddle,
            None
        };

        enum Power
        {
            AllBreaking,
            Slow,
            Shooter,
            Sticky,
            None
        };

        virtual void apply() = 0;
        virtual void createPower() = 0;

        void draw() const
        {
            attron( COLOR_PAIR( m_color ) | m_attributes );
            mvprintw( gety(), getx(), "%%" );
            attrset( A_NORMAL );
        }

        bool intersects( const Point& t_point ) const
        {
            return getx() == t_point.y && getx() == t_point.x;
        }

        void setType( Type t_powerType )
        {
            m_type = t_powerType;
        }

        void setPower( Power t_powerType )
        {
            m_power = t_powerType;
        }

    protected:
        bool m_isDestroyable{ false };
        Power m_power{ Power::None };
        Type  m_type{ Type::None };
};

class BallPowerUp : public PowerUp
{
    public:
        BallPowerUp( PowerUp::Power t_power )
        {
            m_power = t_power;

            switch ( m_power )
            {
                case Power::AllBreaking:
                    setColorPair( Entity::ColorPair::Red );
                    setAttribiutes( A_BOLD );

                    break;
                case Power::Slow:
                    setColorPair( Entity::ColorPair::Yellow );
                    setAttribiutes( A_BOLD );

                    break;
                case Power::Shooter:
                case Power::Sticky:
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
                case Power::Shooter:
                case Power::Sticky:
                case Power::None:
                    break;
            }
        }

    private:
        BallState* m_state{ nullptr };
};

class PaddlePowerUp : public PowerUp
{
    public:
        PaddlePowerUp( PowerUp::Power t_power )
        {
            m_power = t_power;

            switch ( m_power )
            {
                case Power::Shooter:
                    setColorPair( Entity::ColorPair::Cyan );
                    setAttribiutes( A_BOLD );

                    break;
                case Power::Sticky:
                    setColorPair( Entity::ColorPair::Green );
                    setAttribiutes( A_BOLD );

                    break;
                case Power::AllBreaking:
                case Power::Slow:
                case Power::None:
                    break;
            }
        }

        void apply() override
        {
            createPower();
            Map::instance()->getPaddle()->changeState( m_state );
        }

        void createPower() override
        {
            switch ( m_power ) 
            {
                case Power::Shooter:
                    m_state = new PaddleShooter;

                    break;
                case Power::Sticky:
                    m_state = new PaddleSticky;

                    break;
                case Power::AllBreaking:
                case Power::Slow:
                case Power::None:
                    break;
            }
        }

    private:
        PaddleState* m_state{ nullptr };
};

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
                {
                    power = create( PowerUp::Type::Paddle, powerUpId );

                    break;
                }

                default:
                    break;
            }

            return power;
        }

    protected:
        PowerUpFactory();
};

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