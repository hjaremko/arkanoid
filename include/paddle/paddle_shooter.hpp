#ifndef PADDLESHOOTER_H
#define PADDLESHOOTER_H

#include "ball/ball_bullet.hpp"
#include "paddle_normal.hpp"

class paddle_shooter : public paddle_normal
{
public:
    paddle_shooter() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const paddle& paddle ) const override
    {
        paddle_normal::draw( paddle );

        attron( COLOR_PAIR( entity::color_pair::cyan ) | A_BOLD );

        const int mid = paddle.getx() + static_cast<int>( paddle.width() / 2 );

        mvprintw( 3, 5, "$^$ : %d", time_left() );
        mvprintw( paddle.gety(), mid - 1, "$^$" );
        mvprintw( paddle.gety(), paddle.getx(), "$" );
        mvprintw( paddle.gety(), paddle.getx() + paddle.width() - 1, "$" );

        attrset( A_NORMAL );

        if ( time_left() <= 0 )
        {
            const_cast<::paddle*>( &paddle )->set_state(
                std::make_shared<paddle_normal>() );
        }
    }

    auto secondary_action( paddle& paddle ) -> std::any override
    {
        ::ball ball;
        ball.set_position( paddle.gety() - 1,
                           paddle.getx() +
                               static_cast<int>( paddle.width() / 2 ) );

        ball.set_state( std::make_shared<ball_bullet>() );
        ball.set_stopped( false );
        return { ball };
    }

    [[nodiscard]] auto what() const -> std::string override
    {
        return "shooter";
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    inline constexpr static auto duration_ { 500 };
};

#endif
