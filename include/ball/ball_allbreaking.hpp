#ifndef BALLALLBREAKING_H
#define BALLALLBREAKING_H

#include "ball.hpp"
#include "ball_normal.hpp"
#include "ball_state.hpp"

class ball_allbreaking : public ball_normal
{
public:
    ball_allbreaking() : start_tick_( arkanoid::system_clock::ticks )
    {
    }

    [[nodiscard]] auto time_left() const -> arkanoid::system_clock::ticks_type
    {
        return duration_ - ( arkanoid::system_clock::ticks - start_tick_ );
    }

    void draw( const ball& ball ) override
    {
        attron( COLOR_PAIR( static_cast<int>( entity::color_pair::red ) ) |
                A_BOLD );

        mvprintw( 2, 5, "*O  : %d", time_left() );

        mvprintw( last_position_.gety(), last_position_.getx(), "*" );
        mvprintw( ball.gety(), ball.getx(), "%c", ball.get_look() );

        attrset( A_NORMAL );
    }

    void shoot( ball& ball ) override
    {
        last_position_ = ball.get_position();
        ball_normal::shoot( ball );

        if ( time_left() <= 0 )
        {
            ball.set_state( std::make_shared<ball_normal>() );
        }
    }

    [[nodiscard]] auto get_reflection_axis( const ball& ball,
                                            const entity& entity ) const
        -> ball::reflection_axis override
    {
        auto axis = ball::reflection_axis::none;

        if ( dynamic_cast<const paddle*>( &entity ) != nullptr ) // bad
        {
            axis = ball::reflection_axis::vertical;
        }
        else if ( dynamic_cast<const unbreakable_block*>( &entity ) != nullptr )
        {
            axis = ball_normal::get_reflection_axis( ball, entity );
        }

        return axis;
    }

private:
    arkanoid::system_clock::ticks_type start_tick_ { 0 };
    point last_position_;
    inline constexpr static auto duration_ { 1000 };
};

#endif
