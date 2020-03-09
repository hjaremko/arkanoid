#ifndef BALLSLOW_H
#define BALLSLOW_H

#include "ball.hpp"
#include "ball_normal.hpp"

class ball_slow : public ball_normal
{
public:
    ball_slow() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const ball& ball ) override
    {
        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::cyan ) ) |
                A_BOLD );

        mvprintw( 2, 5, "O   : %d", time_left() );
        mvprintw( ball.gety(), ball.getx(), "O" );

        attrset( A_NORMAL );
    }

    void shoot( ball& ball ) override
    {
        if ( ( arkanoid::system_clock::ticks % 20 ) == 0U )
        {
            ball.move_by( ball.get_velocity() );
        }

        if ( time_left() <= 0 )
        {
            ball.set_state( std::make_shared<ball_normal>() );
            ball.set_speed( ball::DEF_SPEED );
        }
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    inline constexpr static auto duration_ { 1000 };
};

#endif
