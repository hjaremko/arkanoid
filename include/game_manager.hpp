#ifndef ARKANOID_GAME_MANAGER_HPP
#define ARKANOID_GAME_MANAGER_HPP

#include "drawing/drawer.hpp"
#include "map.hpp"

#include <algorithm>
#include <ctime>
#include <random>
#include <utility>

namespace arkanoid
{
class game_manager
{
public:
    void update()
    {
        if ( map_.get_paddle()->get_state().what() == "barrier" )
        {
            map_.barrier_on();
        }
        else
        {
            map_.barrier_off();
        }

        update_balls();
        update_powers();

        if ( map_.get_entities().size() <= 1 )
        {
            map_ = map( ++current_level_ );
        }

        if ( map_.get_balls().empty() && !map_.get_paddle()->has_balls() )
        {
            map_ = map( current_level_ );
            // map::instance()->set_message( "Try again :(" );
        }
    }

    auto get_map() -> map&
    {
        return map_;
    }

    void move_paddle( int new_x )
    {
        map_.get_paddle()->set_position(
            { map_.get_paddle()->gety(),
              new_x - ( map_.get_paddle()->width() / 2 ) } );
    }

    void shoot()
    {
        auto balls = map_.get_paddle()->release_balls();
        map_.get_balls().merge( balls );
    }

    void secondary_action()
    {
        auto result = map_.get_paddle()->secondary_action();

        if ( map_.get_paddle()->get_state().what() == "shooter" )
        {
            map_.get_balls().insert(
                std::make_unique<ball>( std::any_cast<ball>( result ) ) );
        }
    }

    static auto random( int min, int max ) -> int
    {
        return std::uniform_int_distribution<int> { min, max }( engine );
    }

private:
    static auto will_collide_with( ball& b, const map::entitiy_set_t& e )
    {
        return std::find_if( begin( e ), end( e ), [&]( auto& e2 ) {
            return e2->intersects( b.get_position() + b.get_velocity() );
        } );
    }

    template <class T, class Predicate>
    static void erase_if( T& container, Predicate predicate )
    {
        for ( auto it = begin( container ); it != end( container ); )
        {
            if ( predicate( *it ) )
            {
                it = container.erase( it );
            }
            else
            {
                ++it;
            }
        }
    }

    void update_balls()
    {
        auto& balls { map_.get_balls() };

        erase_if( balls, []( const auto& ball ) {
            return ball->get_position().is_out() || ball->is_stopped();
        } );

        for ( auto it = begin( balls ); it != end( balls ); )
        {
            const auto& ball = *it;
            ball->shoot();

            if ( auto wall_reflection = ball->get_wall_reflection_axis();
                 wall_reflection != ball::none )
            {
                ball->reflect( wall_reflection );
                ball->change_speed_by( -1 );
                ++it;
                continue;
            }

            auto entity = will_collide_with( *ball, map_.get_entities() );

            if ( entity == end( map_.get_entities() ) )
            {
                ++it;
                continue;
            }

            if ( *entity == map_.get_paddle() &&
                 map_.get_paddle()->get_state().what() == "sticky" )
            {
                auto t = it++;
                auto b = std::move( balls.extract( t ).value() );
                map_.get_paddle()->catch_ball( std::move( b ) );
                continue;
            }

            if ( ( *entity )->can_collide() )
            {
                ball->reflect( ball->get_reflection_axis( **entity ) );
                ball->change_speed_by( -1 );

                if ( ( *entity )->is_destroyable() )
                {
                    map_.destroy( entity );

                    if ( random( 0, 10 ) == 0 )
                    {
                        map_.spawn_power( ball->get_position() );
                    }
                }
            }
            ++it;
        }
    }

    void update_powers()
    {
        auto& powers { map_.get_powers() };

        erase_if( powers,
                  []( const auto& x ) { return x->get_position().is_out(); } );

        erase_if( powers, [&]( auto& x ) {
            if ( map_.get_paddle()->intersects( x->get_position() ) )
            {
                x->apply( map_ );
                return true;
            }

            x->fall();
            return false;
        } );
    }

    static inline std::mt19937 engine { static_cast<unsigned int>(
        time( nullptr ) ) };
    int current_level_ { 1 };
    map map_ { current_level_ };
};
} // namespace arkanoid

#endif // ARKANOID_GAME_MANAGER_HPP
