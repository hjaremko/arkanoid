#include "Map.hpp"
#include "PowerUp.hpp"
#include "PowerUpFactory.hpp"
#include "PowerUpMovement.hpp"

Map* Map::m_instance = nullptr;

Map* Map::instance()
{
    if ( m_instance == nullptr )
    {
        m_instance = new Map;
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

    delete m_instance;
}

void Map::draw() const
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
    m_paddle->setPosition( getmaxy( stdscr ) - 5, 5 );
    auto tmp = newBall();
    tmp->setPosition( m_paddle->gety() - 1, m_paddle->getx() +
                      static_cast<int>( m_paddle->getWidth() / 2 ) );
    m_paddle->getBall( tmp );
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

bool Map::readCurrentLevel()
{
    std::stringstream levelPath;
    levelPath << "levels/level" << currentLevel << ".txt";
    std::ifstream levelFile( levelPath.str().c_str() );
    std::string blockData;

    if ( levelFile.is_open() )
    {
        m_entities.clear();

        for ( auto& ball : m_balls )
            ball->setStopped( true );

        m_balls.clear();
        initPaddle();

        while ( std::getline( levelFile, blockData ) )
        {
            std::stringstream s( blockData );

            int y = 0;
            int x = 0;
            int width = 0;
            int height = 0;
            int color = 1;
            int bold = 1;
            int breakable = 1;

            s >> y >> x >> width >> height >> color >> bold >> breakable;

            Entity* tmp;
            int boldAttr = ( bold ? A_BOLD : 0 );

            if ( breakable == 1 )
            {
                tmp = new Block( static_cast<Entity::ColorPair>( color ), boldAttr, Point( y, x ) );
            }
            else
            {
                tmp = new UnbreakableBlock( static_cast<Entity::ColorPair>( color ), boldAttr, Point( y, x ) );
            }

            tmp->setHeight( height );
            tmp->setWidth( width );
            pushEntity( tmp );
        }

        levelFile.close();

        return true;
    }
    else
    {
        return false;
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
    if ( pos != m_entities.end() )
    {
        // delete *pos;
        // *pos = nullptr;
        m_entities.erase( pos );
    }
} 

void Map::destroyBall( Ball* t_entity )
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

std::vector<Entity*>& Map::getEntities()
{
    return m_entities;
}

std::vector<Ball*>& Map::getBalls()
{
    return m_balls;
}

void Map::spawnPowerUp( const Point& t_point )
{
    auto power = PowerUpFactory::createRandom();
    power->setPosition( t_point );
    m_entities.push_back( power );

    PowerUpMovement bm( power );
    std::thread powerUpThread( bm );
    powerUpThread.detach();
}
