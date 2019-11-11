#include "../include/map.hpp"
#include "../include/power.hpp"
#include "../include/power_factory.hpp"
#include "../include/power_movement.hpp"

map* map::m_instance = nullptr;

map* map::instance()
{
    if ( m_instance == nullptr )
    {
        m_instance = new map;
    }

    return m_instance;
}

map::~map()
{
    for ( const auto& entity : m_entities )
    {
        delete entity;
    }

    for ( const auto& ball : m_balls )
    {
        delete ball;
    }

    delete m_instance;
}

void map::draw() const
{
    m_paddle->draw();

    for ( const auto& entity : m_entities )
    {
        entity->draw();
    }

    for ( const auto& ball : m_balls )
    {
        ball->draw();
    }
}

void map::push_entity( entity* t_entity )
{
    m_entities.push_back( t_entity );
}

ball* map::new_ball()
{
    ball* tmp = new ball;
    m_balls.push_back( tmp );

    return tmp;
}

void map::init_paddle()
{
    m_paddle = new paddle;
    m_paddle->set_width( 15 );
    m_paddle->set_height( 1 );
    m_paddle->set_position( getmaxy( stdscr ) - 5, getmaxx( stdscr ) / 2 - 7 );
    auto tmp = new_ball();
    tmp->set_position( m_paddle->gety() - 1, m_paddle->getx() +
                                             m_paddle->width() / 2 );
    m_paddle->get_ball( tmp );
    push_entity( m_paddle );
}

void map::init_blocks()
{
    int starty = 4;
    int startx = ( getmaxx( stdscr ) - 66 ) / 2;
    int color = 1;
    for ( int i = 0; i < 5; ++i )
    {
        for ( int j = 0; j < 11; ++j )
        {
            auto tmp = new block( static_cast<entity::color_pair>( color % 5 + 1 ), A_BOLD,
                                  point( i * 3 + starty, j * 6 + startx ) );
            tmp->set_height( 3 );
            tmp->set_width( 6 );
            m_entities.push_back( tmp );

            color++;
        }
    }
}

bool map::read_current_level()
{
    std::stringstream level_path;
    level_path << "levels/level" << current_level << ".txt";
    std::ifstream level_file( level_path.str().c_str() );
    std::string block_data;

    if ( level_file.is_open() )
    {
        m_entities.clear();

        for ( auto& ball : m_balls )
            ball->set_stopped( true );

        m_balls.clear();
        init_paddle();

        while ( std::getline( level_file, block_data ) )
        {
            std::stringstream s( block_data );

            int y = 0;
            int x = 0;
            int width = 0;
            int height = 0;
            int color = 1;
            int bold = 1;
            int breakable = 1;

            s >> y >> x >> width >> height >> color >> bold >> breakable;

            entity* tmp;
            auto bold_attr = ( bold ? A_BOLD : 0 );

            if ( breakable == 1 )
            {
                tmp = new block( static_cast<entity::color_pair>( color ), bold_attr, point( y, x ) );
            }
            else
            {
                tmp = new unbreakable_block( static_cast<entity::color_pair>( color ), bold_attr, point( y, x ) );
            }

            tmp->set_height( height );
            tmp->set_width( width );
            push_entity( tmp );
        }

        level_file.close();

        return true;
    }
    else
    {
        return false;
    }
}

paddle* map::get_paddle() const
{
    return m_paddle;
}

ball* map::get_ball( unsigned int t_id ) const
{
    return m_balls.at( t_id );
}

entity* map::get_entity_at( unsigned int t_id ) const
{
    return m_entities.at( t_id );
}

void map::destroyAt( unsigned int t_entity )
{
    delete m_entities.at( t_entity );
    m_entities.erase( begin( m_entities ) + t_entity );
}

void map::destroy( entity* t_entity )
{
    auto pos = std::find( m_entities.begin(), m_entities.end(), t_entity );
    if ( pos != m_entities.end() )
    {
        // delete *pos;
        // *pos = nullptr;
        m_entities.erase( pos );
    }
} 

void map::destroy_ball( ball* t_entity )
{
    std::mutex mutex;
    auto pos = std::find( m_balls.begin(), m_balls.end(), t_entity );

    if ( pos != m_balls.end() )
    {
        mutex.lock();
        // delete *pos;
        // *pos = nullptr;
        m_balls.erase( pos );
        mutex.unlock();
    }
}

std::vector<entity*>& map::get_entities()
{
    return m_entities;
}

std::vector<ball*>& map::get_balls()
{
    return m_balls;
}

void map::spawn_power( const point& t_point )
{
    auto power = power_factory::create_random();
    power->set_position( t_point );
    m_entities.push_back( power );

    power_movement bm( power );
    std::thread power_thread( bm );
    power_thread.detach();
}
