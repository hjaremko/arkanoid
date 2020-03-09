#ifndef ARKANOID_PADDLE_STICKY_HPP
#define ARKANOID_PADDLE_STICKY_HPP

#include "paddle_normal.hpp"
#include "system_clock.hpp"

// TODO: uses instead of time
class paddle_sticky : public paddle_normal
{
public:
    paddle_sticky() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const paddle& paddle ) const override
    {
        attron( COLOR_PAIR( paddle.get_color() ) | paddle.get_attributes() );

        for ( int i = 0; i < paddle.height(); ++i )
        {
            for ( int j = 0; j < paddle.width(); ++j )
            {
                attron( COLOR_PAIR( entity::color_pair::green ) | A_BOLD );
                mvprintw( paddle.gety() - 1, paddle.getx() + j, "_" );
                mvprintw( paddle.gety(), paddle.getx() - 1, "/" );
                mvprintw( paddle.gety(), paddle.getx() + paddle.width(), "\\" );

                attrset( A_NORMAL );

                mvprintw( paddle.gety(), paddle.getx() + j, "@" );
            }
        }

        attron( COLOR_PAIR( entity::color_pair::green ) | A_BOLD );
        mvprintw( 3, 5, "~~~ : %d", time_left() );
        attrset( A_NORMAL );

        if ( time_left() <= 0 )
        {
            const_cast<::paddle*>( &paddle )->set_state(
                std::make_shared<paddle_normal>() );
        }
    }

    [[nodiscard]] auto what() const -> std::string override
    {
        return "sticky";
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    inline constexpr static auto duration_ { 2000 };
};

#endif // ARKANOID_PADDLE_STICKY_HPP
