#include <utility>

#ifndef MAP_H
#define MAP_H

#include "ball.hpp"
#include "block.hpp"
#include "entity.hpp"
#include "paddle.hpp"

#include <algorithm>
#include <curses.h>
#include <fstream>
#include <sstream>
#include <vector>

class map
{
public:
    ~map();
    void draw() const;
    void destroyAt( unsigned int );
    void destroy( entity* );
    void destroy_ball( ball* );
    void push_entity( entity* );
    void init_paddle();
    void init_blocks();
    void spawn_power( const point& t_point );
    ball* new_ball();
    ball* get_ball( unsigned int ) const;
    entity* get_entity_at( unsigned int ) const;
    paddle* get_paddle() const;
    std::vector<entity*>& get_entities();
    std::vector<ball*>& get_balls();
    bool read_current_level();

    void set_message( std::string t_msg )
    {
        m_message = std::move( t_msg );
    }

    void draw_message()
    {
        mvprintw( 1, 5, "%s", m_message.c_str() );
    }

    static map* instance();

    int current_level { 1 };

protected:
    map() = default;

private:
    std::vector<entity*> m_entities;
    std::vector<ball*> m_balls;
    std::string m_message;
    paddle* m_paddle { nullptr };

    static map* m_instance;
};

#endif // MAP_H
