#ifndef MAP_H
#define MAP_H

#include <vector>
#include <algorithm>
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
        void    pushEntity( Entity* );
        void    initPaddle();
        void    initBlocks();
        Ball*   newBall();
        Ball*   getBall( const int ) const;
        Entity* getEntityAt( const int ) const;
        Paddle* getPaddle() const;
        void    spawnPowerUp( const Point& t_point );
        std::vector<Entity*>* getEntities();

        static Map* instance();

    protected:
        Map();

    private:
        std::vector<Entity*> m_entities;
        std::vector<Ball*>   m_balls;
        Paddle*              m_paddle{ nullptr };

        static Map* m_instance;
};

#endif //MAP_H
