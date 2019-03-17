#ifndef MAPDRAWING_H
#define MAPDRAWING_H

#include "src/map.hpp"

class map_drawing
{
    public:
        map_drawing() = default;

        void operator()() const
        {
            while ( true )
            {
                if ( map::instance()->get_balls().size() == 0 )
                {
                    map::instance()->read_current_level();
                    map::instance()->set_message( "Try again :(" );
                }

                if ( map::instance()->get_entities().size() == 1 )
                {
                    map::instance()->current_level++;

                    if ( !map::instance()->read_current_level() )
                    {
                        map::instance()->set_message( "You won!" );
                    }
                }

                clear();
                map::instance()->draw();
                map::instance()->draw_message();
                refresh();
            }
        }
};

#endif
