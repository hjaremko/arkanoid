#ifndef BALLWEIRD_H
#define BALLWEIRD_H

#include "ball.hpp"
#include "ball_normal.hpp"
#include "game_manager.hpp"

class ball_weird : public ball_normal
{
public:
    ball_weird() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const ball& ball ) override
    {
        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::yellow ) ) |
                A_BOLD );

        mvprintw( 2, 5, "O   : %d", time_left() );
        mvprintw( ball.gety(), ball.getx(), "O" );

        attrset( A_NORMAL );
    }

    void shoot( ball& ball ) override
    {
        ball_normal::shoot( ball );

        if ( time_left() <= 0 )
        {
            ball.set_state( std::make_shared<ball_normal>() );
            ball.set_speed( ball::DEF_SPEED );
        }
    }

    [[nodiscard]] auto get_reflection_axis( const ball& /*unused*/,
                                            const entity& entity ) const
        -> ball::reflection_axis override
    {
        if ( dynamic_cast<const paddle*>( &entity ) != nullptr )
        {
            return ball::reflection_axis::vertical;
        }

        // TODO: find out if inclusive
        const auto axis = arkanoid::game_manager::random( 1, 3 );
        return static_cast<ball::reflection_axis>( axis );
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    inline constexpr static auto duration_ { 2000 };
};

#endif
