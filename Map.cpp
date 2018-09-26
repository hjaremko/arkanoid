#include "Map.hpp"

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
        ball->draw();
    }

    m_paddle->draw();
    refresh();
}

void Map::pushEntity( Entity* t_entity )
{
    m_entities.push_back( t_entity );
}

Ball* Map::newBall()
{
    Ball* tmp = new Ball( &m_entities );
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
    int starty = 1;
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

Entity* Map::getEntity( const int t_id ) const
{
    return m_entities.at( t_id );
}

void Map::destroy( const int t_entity )
{
    delete m_entities.at( t_entity );
    m_entities.erase( begin( m_entities ) + t_entity );
} 
