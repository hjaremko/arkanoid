#ifndef PADDLE_H
#define PADDLE_H

#include "ball/ball.hpp"
#include "entity.hpp"
#include "paddle_state.hpp"

#include <any>
#include <unordered_set>

class paddle : public entity
{
public:
    using ball_ptr = std::unique_ptr<ball>;
    using state_ptr = std::shared_ptr<paddle_state>;

    paddle();
    paddle( const paddle& ) = delete;
    paddle( paddle&& ) = default;
    auto operator=( const paddle& ) -> paddle& = delete;
    auto operator=( paddle && ) -> paddle& = default;
    ~paddle() override = default;

    void catch_ball( ball_ptr ball );
    auto release_balls() -> std::unordered_set<ball_ptr>;
    void draw() const override;
    void set_position( const point& /*t_pos*/ ) override;
    void set_position( int /*t_y*/, int /*t_x*/ ) override;
    void set_width( int /*t_width*/ ) override;
    [[nodiscard]] auto width() const -> int override;
    [[nodiscard]] auto intersects( const point& /*t_point*/ ) const
        -> bool override;
    auto secondary_action() -> std::any;
    void set_state( state_ptr );

    [[nodiscard]] auto get_state() const -> const paddle_state&
    {
        return *state_;
    }

    void change_size_by( int );
    [[nodiscard]] auto is_destroyable() const -> bool override;

    auto has_balls() const -> bool
    {
        return !balls_.empty();
    }

    static constexpr auto MAX_WIDTH = 37;
    static constexpr auto MIN_WIDTH = 5;

private:
    std::unordered_set<ball_ptr> balls_;
    state_ptr state_;
};

auto make_paddle() -> paddle;

#endif // PADDLE_H
