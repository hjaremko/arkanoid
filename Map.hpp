#ifndef MAP_H
#define MAP_H

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <curses.h>

#include "Entity.hpp"
#include "Block.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

class Map
{
    public:
        ~Map();
        void    draw() const;
        void    destroyAt( const int );
        void    destroy( Entity* );
        void    destroyBall( Ball* );
        void    pushEntity( Entity* );
        void    initPaddle();
        void    initBlocks();
        void    spawnPowerUp( const Point& t_point );
        Ball*   newBall();
        Ball*   getBall( const int ) const;
        Entity* getEntityAt( const int ) const;
        Paddle* getPaddle() const;
        std::vector<Entity*>& getEntities();
        std::vector<Ball*>&   getBalls();
        bool readCurrentLevel();

        void setMessage( std::string  t_msg )
        {
            m_message = t_msg;
        }

        void drawMessage()
        {
            mvprintw( 1, 5, "%s", m_message.c_str() );
        }

        static Map* instance();

        int currentLevel{ 1 };
    protected:
        Map();

    private:
        std::vector<Entity*> m_entities;
        std::vector<Ball*>   m_balls;
        std::string          m_message{ "" };
        Paddle*              m_paddle{ nullptr };

        static Map* m_instance;
};

#endif //MAP_H
