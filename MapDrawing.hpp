#ifndef MAPDRAWING_H
#define MAPDRAWING_H

#include "Map.hpp"

class MapDrawing
{
    public:
        MapDrawing( Map* t_map ) : m_map( t_map ) {}

        void operator()() const
        {
            while ( true )
            {
                clear();
                m_map->draw();
            }
        }

    private:
        Map* m_map{ nullptr };
};

#endif
