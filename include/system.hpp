#ifndef ARKANOID_SYSTEM_HPP
#define ARKANOID_SYSTEM_HPP

#include "drawing/drawer.hpp"
#include "game_manager.hpp"
#include "system_clock.hpp"

#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

namespace arkanoid
{
class system
{
public:
    system() : system_loop_( std::thread( &system::system_loop, this ) )
    {
    }

    ~system()
    {
        stop();
    }

    void system_loop()
    {
        while ( is_running_ )
        {
            while ( !task_queue_.empty() )
            {
                std::lock_guard<std::mutex> lock( task_mutex_ );
                task_queue_.front()( game_manager_ );
                task_queue_.pop_front();
            }

            game_manager_.update();
            drawer_.draw( game_manager_.get_map() );
            system_clock::ticks++;
        }
    }

    void stop()
    {
        is_running_ = false;

        if ( system_loop_.joinable() )
        {
            system_loop_.join();
        }
    }

    [[maybe_unused]] void start()
    {
        is_running_ = true;
        system_loop_ = std::thread( &system::system_loop, this );
    }

    template <class Task>
    void push_task( Task task )
    {
        const std::lock_guard<std::mutex> lock( task_mutex_ );
        task_queue_.push_back( task );
    }

//    using ticks_type = unsigned long long;
    //    inline static auto ticks { ticks_type { 0 } };

private:
    std::mutex task_mutex_;
    std::deque<std::function<void( game_manager& )>> task_queue_;
    bool is_running_ { true };
    drawer drawer_;
    game_manager game_manager_;
    std::thread system_loop_;
};
} // namespace arkanoid

#endif // ARKANOID_SYSTEM_HPP
