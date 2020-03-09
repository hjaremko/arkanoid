#ifndef PADDLESTATE_H
#define PADDLESTATE_H

#include <any>

class paddle;

class paddle_state
{
public:
    paddle_state() = default;
    paddle_state( const paddle_state& ) = default;
    paddle_state( paddle_state&& ) = default;
    auto operator=( const paddle_state& ) -> paddle_state& = default;
    auto operator=( paddle_state && ) -> paddle_state& = default;
    virtual ~paddle_state() = default;

    virtual void draw( const paddle& ) const = 0;
    virtual auto secondary_action( paddle& ) -> std::any = 0;
    virtual auto intersects( const paddle&, const point& ) -> bool = 0;
    [[nodiscard]] virtual auto what() const -> std::string = 0;
};

#endif
