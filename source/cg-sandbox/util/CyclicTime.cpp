#include "CyclicTime.h"

#include <cassert>

CyclicTime::CyclicTime(value_type secondsPerCycle)
:   m_secondsPerCycle(secondsPerCycle)
,   m_current(0)
{
    assert(secondsPerCycle > value_type(0));
}

CyclicTime::~CyclicTime()
{
}

void CyclicTime::update()
{
    m_timer.update();
}

CyclicTime::value_type CyclicTime::time() const
{
    return std::chrono::duration_cast<std::chrono::duration<value_type>>(m_timer.elapsed()).count() / m_secondsPerCycle;
}

CyclicTime::value_type CyclicTime::normalizedTime() const
{
    return time() / m_secondsPerCycle;
}

void CyclicTime::start()
{
    m_timer.start();
}

void CyclicTime::pause()
{
    m_timer.pause();
}

void CyclicTime::reset()
{
    m_timer.stop();
    m_timer.start();
}

void CyclicTime::stop()
{
    m_timer.stop();
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
    return !m_timer.paused() && !m_timer.stopped();
}
