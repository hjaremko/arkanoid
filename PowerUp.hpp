#ifndef POWERUP_H
#define POWERUP_H

#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Map.hpp"
#include "BallState.hpp"

class PowerUp : public Entity
{
    public:
        PowerUp()
        {
            m_power = rand() % 2;
            
            switch ( m_power )
            {
                case 0:
                    setColorPair( ColorPair::Red );
                    break;
                case 1:
                    setColorPair( ColorPair::Yellow );
                    setAttribiutes( A_BOLD );
                    break;
            }
        };

        ~PowerUp() {};
    
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

    BallState* getPower() const
    {
        switch ( m_power )
        {
            case 0:
                return new BallAllBreaking;
                break;
            case 1:
                return new BallSlow;
                break;
        }
    }

    protected:
        bool m_isDestroyable{ false };

    private:
        int m_power{ 0 };
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

            Map::instance()->destroy( m_power );
            Map::instance()->getBall( 0 )->changeState( m_power->getPower() );
        }

    private:
        PowerUp* m_power{ nullptr };
};

#endif