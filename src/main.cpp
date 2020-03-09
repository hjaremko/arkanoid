#include "events/event_handler.hpp"
#include "system.hpp"

auto main() -> int
{
    arkanoid::system system;
    event_handler event_handler { system };

    while ( event_handler.fetch_event() )
    {
    }

    return 0;
}
