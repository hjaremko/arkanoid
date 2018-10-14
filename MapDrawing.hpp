#ifndef MAPDRAWING_H
#define MAPDRAWING_H

#include "Map.hpp"

class MapDrawing
{
    public:
        MapDrawing() {}

        void operator()() const
        {
            while ( true )
            {
                clear();
                Map::instance()->draw();
                refresh();
            }
        }
};

#endif
