#pragma once

#include <cstdint>
#include <chrono>

class ChronoTimer
{
public:
    using clock = std::chrono::high_resolution_clock;
    using time_point = clock::time_point;
    using nano = std::chrono::duration<std::uint64_t, std::nano>;

    ChronoTimer();
    virtual ~ChronoTimer();

    nano elapsed() const;

    void reset(const time_point & timePoint = clock::now());

    nano restart();

protected:
    time_point m_start;
};
