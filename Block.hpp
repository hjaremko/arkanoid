#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.hpp"

class Block : public Entity
{
    public:
        Block();
        void draw() const;
        void destroy() const;

    private:
};

#endif //BLOCK_H
