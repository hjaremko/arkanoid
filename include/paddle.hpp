#ifndef PADDLE_H
#define PADDLE_H

#include "ball.hpp"
#include "entity.hpp"
#include "point.hpp"

#include <chrono>
#include <curses.h>
#include <thread>

class paddle_state;

class paddle : public entity
{
public:
    paddle();
    ~paddle() override;
    ball* get_ball( ball* );
    void draw() const override;
    void move( int, int );
    void shoot();
    void set_position( const point& ) override;
    void set_position( int, int ) override;
    void set_width( int ) override;
    int width() const override;
    bool intersects( const point& ) const override;
    void secondary_action();
    void set_state( paddle_state* );
    void change_size_by( int );
    bool is_destroyable() const override;

    static const int MAX_WIDTH = 37;
    static const int MIN_WIDTH = 5;

private:
    std::vector<ball*> m_balls;
    paddle_state* m_state { nullptr };
};

#endif // PADDLE_H
