#ifndef BALLSTATE_H
#define BALLSTATE_H

#include "ball.hpp"
#include "map.hpp"
#include "paddle.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::steady_clock;

class ball_state
{
public:
    virtual ~ball_state() = default;
    virtual void draw( const ball* ) = 0;
    virtual void shoot( ball* ) = 0;
    virtual void reflect( ball*, ball::reflection_axis ) = 0;
    virtual ball::reflection_axis get_reflection_axis( const ball*, entity* ) const = 0;

    virtual void set_state( ball* t_ball, ball_state* t_state )
    {
        delete t_ball->m_state;

        t_ball->m_state = t_state;
        t_ball->set_speed( ball::DEF_SPEED );
    }

    explicit operator bool() const
    {
        return m_null;
    }

private:
    bool m_null { false };
};

#endif
