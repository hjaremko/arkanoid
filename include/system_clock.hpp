#ifndef ARKANOID_SYSTEM_CLOCK_HPP
#define ARKANOID_SYSTEM_CLOCK_HPP

namespace arkanoid
{
struct system_clock
{
    using ticks_type = unsigned long long;
    inline static auto ticks { ticks_type { 0 } };
};
} // namespace arkanoid

#endif // ARKANOID_SYSTEM_CLOCK_HPP
