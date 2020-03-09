#include "map.hpp"

#include "block.hpp"
#include "power/power_factory.hpp"

#include <ostream>

namespace arkanoid
{
map::map( int level_id )
    : paddle_( std::make_shared<paddle>( make_paddle() ) ),
      barrier_( std::make_shared<unbreakable_block>(
          entity::color_pair::blue, 0, point( getmaxy( stdscr ) - 2, 0 ) ) )
{
    barrier_->set_width( getmaxx( stdscr ) );
    barrier_->set_height( 1 );
    barrier_->set_look( '=' );
    entities_.insert( paddle_ );
    read_level( level_id );
}

void map::barrier_on()
{
    entities_.insert( barrier_ );
}

void map::barrier_off()
{
    if ( const auto it =
             std::find( begin( entities_ ), end( entities_ ), barrier_ );
         it != end( entities_ ) )
    {
        entities_.erase( it );
    }
}

void map::draw() const
{
    for ( const auto& entity : entities_ )
    {
        entity->draw();
    }

    for ( const auto& ball : balls_ )
    {
        ball->draw();
    }

    for ( const auto& power : powers_ )
    {
        power->draw();
    }
}

void map::spawn_power( const point& t_point )
{
    auto power = power_factory::create_random();
    power->set_position( t_point );
    powers_.insert( std::move( power ) );
}

void map::init_blocks()
{
    int start_y = 4;
    int start_x = ( getmaxx( stdscr ) - 66 ) / 2;
    int color = 1;
    for ( int i = 0; i < 5; ++i )
    {
        for ( int j = 0; j < 11; ++j )
        {
            auto tmp = std::make_shared<block>(
                static_cast<entity::color_pair>( color % 5 + 1 ),
                A_BOLD,
                point( i * 3 + start_y, j * 6 + start_x ) );
            tmp->set_height( 3 );
            tmp->set_width( 6 );
            tmp->set_position( { i * 3 + start_y, j * 6 + start_x } );
            entities_.insert( tmp );

            color++;
        }
    }
}

auto map::read_level( int level_id ) -> bool
{
    std::stringstream level_path;
    level_path << "levels/level" << level_id << ".txt";
    std::ifstream level_file( level_path.str().c_str() );
    std::string block_raw_data;

    if ( !level_file.is_open() )
    {
        init_blocks();
        return false;
    }

    std::vector<block_data> blocks;

    while ( std::getline( level_file, block_raw_data ) )
    {
        std::stringstream s( block_raw_data );
        block_data temp;
        s >> temp;
        blocks.push_back( temp );
    }

    const auto min_x =
        std::min_element(
            begin( blocks ),
            end( blocks ),
            []( const auto& lhs, const auto& rhs ) { return lhs.x < rhs.x; } )
            ->x;

    for ( const auto& data : blocks )
    {
        auto tmp = data.to_shared_ptr();
        tmp->setx( data.x - min_x + getmaxx( stdscr ) / 4 );
        entities_.insert( tmp );
    }

    // TODO: some message
    level_file.close();
    return true;
}

} // namespace arkanoid
