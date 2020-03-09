#ifndef PADDLEBARRIER_H
#define PADDLEBARRIER_H

#include "paddle.hpp"
#include "paddle_normal.hpp"

class paddle_barrier : public paddle_normal
{
public:
    paddle_barrier() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const paddle& t_paddle ) const override
    {
        paddle_normal::draw( t_paddle );

        attron( COLOR_PAIR( entity::color_pair::blue ) | A_BOLD );
        mvprintw( 3, 5, "== : %d", time_left() );
        attrset( A_NORMAL );

        if ( time_left() <= 0 )
        {
            const_cast<paddle*>( &t_paddle )
                ->set_state( std::make_shared<paddle_normal>() );
        }
    }

    [[nodiscard]] auto what() const -> std::string override
    {
        return "barrier";
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    inline constexpr static auto duration_ { 2000 };
};

#endif
