#ifndef ARKANOID_MAP_HPP
#define ARKANOID_MAP_HPP

#include "paddle/paddle.hpp"
#include "power/power.hpp"
#include "unbreakable_block.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_set>
#include <utility>

namespace arkanoid
{
class map
{
public:
    using entitiy_set_t = std::unordered_set<std::shared_ptr<entity>>;
    using ball_set_t = std::unordered_set<std::unique_ptr<ball>>;
    using power_set_t = std::unordered_set<std::shared_ptr<power>>;

    explicit map( int level_id = 1 );

    void barrier_on();
    void barrier_off();
    void draw() const;
    void spawn_power( const point& t_point );

    template <class T>
    void destroy( const T& it )
    {
        entities_.erase( it );
    }

    [[nodiscard]] auto get_paddle() const -> std::shared_ptr<paddle>
    {
        return paddle_;
    }

    auto get_entities() -> entitiy_set_t&
    {
        return entities_;
    }

    auto get_balls() -> ball_set_t&
    {
        return balls_;
    }

    auto get_powers() -> power_set_t&
    {
        return powers_;
    }

    //    void set_message( std::string t_msg )
    //    {
    //        m_message = std::move( t_msg );
    //    }

    //    void draw_message()
    //    {
    //        mvprintw( 1, 5, "%s", m_message.c_str() );
    //    }

private:
    auto read_level( int ) -> bool;
    void init_blocks();

    entitiy_set_t entities_;
    ball_set_t balls_;
    power_set_t powers_;

    //    std::string message_;
    std::shared_ptr<paddle> paddle_;
    std::shared_ptr<unbreakable_block> barrier_;
};
} // namespace arkanoid

struct block_data
{
    int y = 0;
    int x = 0;
    int width = 0;
    int height = 0;
    int color = 1;
    int bold = 1;
    int breakable = 1;

    [[nodiscard]] auto to_shared_ptr() const -> std::shared_ptr<block>
    {
        auto tmp = std::shared_ptr<block>();
        auto bold_attr = ( bold != 0 ? A_BOLD : 0 );

        if ( breakable == 1 )
        {
            tmp = std::make_shared<block>(
                static_cast<entity::color_pair>( color ),
                bold_attr,
                point( y, x ) );
        }
        else
        {
            tmp = std::make_shared<unbreakable_block>(
                static_cast<entity::color_pair>( color ),
                bold_attr,
                point( y, x ) );
        }

        tmp->set_height( height );
        tmp->set_width( width );

        return tmp;
    }

    friend auto operator>>( std::istream& os, block_data& data )
        -> std::istream&
    {
        return os >> data.y >> data.x >> data.width >> data.height >>
               data.color >> data.bold >> data.breakable;
    }
};

#endif // MAP_H
