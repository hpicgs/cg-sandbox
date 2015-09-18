#include "CyclicTime.h"

#include <cmath>
#include <cassert>
#include <algorithm>

CyclicTime::CyclicTime(value_type secondsPerCycle)
:   m_paused(false)
,   m_secondsPerCycle(secondsPerCycle)
,   m_current(0)
{
    assert(secondsPerCycle > value_type(0));
}

CyclicTime::~CyclicTime()
{
}

CyclicTime::value_type CyclicTime::time() const
{
    if (m_paused)
    {
        return m_pausedTime;
    }

    const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<value_type>>(m_timer.elapsed()).count();

    return elapsedTime - (m_secondsPerCycle * std::floor(elapsedTime / m_secondsPerCycle));
}

CyclicTime::value_type CyclicTime::normalizedTime() const
{
    return time() / m_secondsPerCycle;
}

void CyclicTime::start()
{
    m_timer.reset();

    m_paused = false;
}

void CyclicTime::pause()
{
    if (m_paused)
    {
        m_timer.reset(ChronoTimer::clock::now() - std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<value_type>(m_pausedTime)));

        m_paused = false;
    }
    else
    {
        m_pausedTime = time();

        m_paused = true;
    }
}

void CyclicTime::reset()
{
    m_timer.reset();
    m_pausedTime = 0.0;
}

CyclicTime::value_type CyclicTime::getSecondsPerCycle() const
{
    return m_secondsPerCycle;
}

void CyclicTime::setSecondsPerCycle(value_type secondsPerCycle)
{
    assert(secondsPerCycle > value_type(0));

    m_secondsPerCycle = secondsPerCycle;
}

bool CyclicTime::isRunning() const
{
    return !m_paused;
}
