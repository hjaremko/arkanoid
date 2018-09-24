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
        Map();
        ~Map();
        void    draw() const;
        void    destroy( const int t_entity );
        void    pushEntity( Entity* t_entity );
        void    initPaddle();
        void    initBlocks();
        Ball*   newBall();
        Ball*   getBall( const int t_id ) const;
        Entity* getEntity( const int t_id ) const;
        Paddle* getPaddle() const;

    private:
        std::vector<Entity*> m_entities;
        std::vector<Ball*>   m_balls;
        Paddle*              m_paddle{ nullptr };
};

#endif //MAP_H
