

#include "ChronoTimer.h"

ChronoTimer::ChronoTimer()
{
    reset();
}

ChronoTimer::~ChronoTimer()
{
}

void ChronoTimer::reset(const time_point & timePoint)
{
    m_start = timePoint;
}

ChronoTimer::nano ChronoTimer::restart()
{
    const auto current = clock::now();
    const auto duration = current - m_start;
    m_start = current;

    return duration;
}

ChronoTimer::nano ChronoTimer::elapsed() const
{
    return clock::now() - m_start;
}
