#ifndef BALL_H
#define BALL_H

#include "entity.hpp"
#include "point.hpp"
#include "system_clock.hpp"

#include <curses.h>
#include <memory>
#include <vector>

class ball : public entity
{
public:
    friend class ball_state;
    using state_ptr = std::shared_ptr<ball_state>;

    enum reflection_axis
    {
        horizontal = 1,
        vertical = 2,
        backwards = 3,
        none = 0
    };

    ball();
    ball( const ball& ) = default;
    ball( ball&& ) = default;
    auto operator=( const ball& ) -> ball& = default;
    auto operator=( ball && ) -> ball& = default;
    ~ball() override = default;

    void draw() const override;
    void move_by( int, int );
    void move_by( const point& );
    void shoot();
    void reflect( reflection_axis );
    void set_vectorY( int );
    void set_vectorX( int );
    void set_speed( arkanoid::system_clock::ticks_type );
    void change_speed_by( arkanoid::system_clock::ticks_type );
    void set_state( state_ptr );
    void set_stopped( bool );
    [[nodiscard]] auto is_stopped() const -> bool;
    [[nodiscard]] auto intersects( const point&  /*point*/) const -> bool override;
    [[nodiscard]] auto get_look() const -> char;
    [[nodiscard]] auto get_speed() const -> arkanoid::system_clock::ticks_type;
    [[nodiscard]] auto get_velocity() const -> point;
    [[nodiscard]] auto get_wall_reflection_axis() const -> reflection_axis;
    [[nodiscard]] auto get_reflection_axis( const entity& ) const
        -> reflection_axis;
    [[nodiscard]] auto get_state() const -> ball_state&;

    static constexpr auto MIN_SPEED { 3 };
    static constexpr auto DEF_SPEED { 8 };

private:
    arkanoid::system_clock::ticks_type speed_ { DEF_SPEED };
    state_ptr state_;
    point velocity_ { point( -1, 1 ) };
    char look_ { 'O' };
    bool is_stopped_ { true };
};

#endif // BALL_H
