#include "Map.hpp"
#include "PowerUp.hpp"

Map* Map::m_instance = 0;

Map* Map::instance()
{
    if ( m_instance == 0 )
    {
        m_instance = new Map();
    }

    return m_instance;
}

Map::Map()
{

}

Map::~Map()
{
    for ( const auto& entity : m_entities )
    {
        delete entity;
    }

    for ( const auto& ball : m_balls )
    {
        delete ball;
    }
}

void Map::draw() const
{
    for ( const auto& entity : m_entities )
    {
        entity->draw();
    }

    for ( const auto& ball : m_balls )
    {
        if ( !ball->isNull() )
        {
            ball->draw();
        }
    }

    m_paddle->draw();
}

void Map::pushEntity( Entity* t_entity )
{
    m_entities.push_back( t_entity );
}

Ball* Map::newBall()
{
    Ball* tmp = new Ball;
    m_balls.push_back( tmp );

    return tmp;
}

void Map::initPaddle()
{
    m_paddle = new Paddle;
    m_paddle->setWidth( 15 );
    m_paddle->setHeight( 1 );
    m_paddle->setPosition( Point( 25, 5 ) );
    m_paddle->getBall( newBall() );
    pushEntity( m_paddle );
}

void Map::initBlocks()
{
    int starty = 4;
    int startx = ( getmaxx( stdscr ) - 66 ) / 2;
    int color = 1;
    for ( int i = 0; i < 5; ++i )
    {
        for ( int j = 0; j < 11; ++j )
        {
            auto tmp = new Block( static_cast<Entity::ColorPair>( color % 5 + 1 ), A_BOLD, Point( i * 3 + starty, j * 6 + startx ) );
            tmp->setHeight( 3 );
            tmp->setWidth( 6 );
            m_entities.push_back( tmp );

            color++;
        }
    }
}

Paddle* Map::getPaddle() const
{
    return m_paddle;
}

Ball* Map::getBall( const int t_id ) const
{
    return m_balls.at( t_id );
}

Entity* Map::getEntityAt( const int t_id ) const
{
    return m_entities.at( t_id );
}

void Map::destroyAt( const int t_entity )
{
    delete m_entities.at( t_entity );
    m_entities.erase( begin( m_entities ) + t_entity );
}

void Map::destroy( Entity* t_entity )
{
    auto pos = std::find( m_entities.begin(), m_entities.end(), t_entity );
    delete *pos;
    m_entities.erase( pos );
} 

std::vector<Entity*>* Map::getEntities()
{
    return &m_entities;
}

void Map::spawnPowerUp( const Point& t_point )
{
    PowerUp* power = new PowerUp;
    power->setPosition( t_point );
    m_entities.push_back( power );

    PowerUpMovement bm( power );
    std::thread powerUpThread( bm );
    powerUpThread.detach();
}
