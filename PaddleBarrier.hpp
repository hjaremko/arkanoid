#ifndef PADDLEBARRIER_H
#define PADDLEBARRIER_H

#include "Paddle.hpp"
#include "PaddleNormal.hpp"

class PaddleBarrier : public PaddleState
{
    public:
        PaddleBarrier()
        {
            startTimePoint = steady_clock::now();

            m_barrier = new UnbreakableBlock( Entity::ColorPair::Green, 0, Point( getmaxy( stdscr ) - 2, 0 ) );
            m_barrier->setWidth( getmaxx( stdscr ) );
            m_barrier->setHeight( 1 );
            m_barrier->setLook( '~' );

            Map::instance()->pushEntity( m_barrier );
        }

        ~PaddleBarrier()
        {
            if ( m_barrier )
            {
                Map::instance()->destroy( m_barrier );
            }
        }

        void draw( const Paddle* t_paddle ) const override
        {
            auto end = steady_clock::now();
            auto left = duration -
                        duration_cast<seconds>( end - startTimePoint ).count();

            attron( COLOR_PAIR( t_paddle->getColor() ) | t_paddle->getAttributes() );

            for ( int i = 0; i < t_paddle->getHeight(); ++i )
            {
                for ( int j = 0; j < t_paddle->getWidth(); ++j )
                {
                    mvprintw( t_paddle->gety(), t_paddle->getx() + j, "@" );
                }
            }

            attron( COLOR_PAIR( Entity::ColorPair::Green ) | A_BOLD );

            mvprintw( 3, 5, "~~~ : %d", left );

            attrset( A_NORMAL );


            auto elapsed = duration_cast<seconds>( end - startTimePoint ).count();

            if ( elapsed >= duration )
            {
                const_cast<Paddle*>( t_paddle )->changeState( new PaddleNormal );
                Map::instance()->destroy( m_barrier );
            }

        }

        void secondaryAction( Paddle* t_paddle ) override
        {
        }

    private:
        steady_clock::time_point startTimePoint;
        UnbreakableBlock* m_barrier{ nullptr };
        int duration{ 15 };
};

#endif
