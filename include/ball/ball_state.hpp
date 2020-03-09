#ifndef BALLSTATE_H
#define BALLSTATE_H

#include "ball.hpp"

class ball_state
{
public:
    ball_state() = default;
    ball_state( const ball_state& ) = default;
    ball_state( ball_state&& ) = default;
    auto operator=( const ball_state& ) -> ball_state& = default;
    auto operator=( ball_state && ) -> ball_state& = default;
    virtual ~ball_state() = default;

    virtual void draw( const ball& ) = 0;
    virtual void shoot( ball& ) = 0;
    virtual void reflect( ball&, ball::reflection_axis ) = 0;
    [[nodiscard]] virtual auto get_reflection_axis( const ball&,
                                                    const entity& ) const
        -> ball::reflection_axis = 0;
};

#endif
