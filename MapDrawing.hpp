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
                if ( Map::instance()->getBalls().size() == 0 )
                {
                    Map::instance()->readCurrentLevel();
                    Map::instance()->setMessage( "Try again :(" );
                }

                if ( Map::instance()->getEntities().size() == 1 )
                {
                    Map::instance()->currentLevel++;

                    if ( !Map::instance()->readCurrentLevel() )
                    {
                        Map::instance()->setMessage( "You won!" );
                    }
                }

                clear();
                Map::instance()->draw();
                Map::instance()->drawMessage();
                refresh();
            }
        }
};

#endif
