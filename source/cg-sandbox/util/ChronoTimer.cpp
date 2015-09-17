

#include "ChronoTimer.h"

ChronoTimer::ChronoTimer(
    const bool start
,   const bool autoUpdate)
:   m_paused(true)
,   m_stopped(true)
,   m_auto(autoUpdate)
{
    if (start)
    {
        this->start();
    }
}

ChronoTimer::~ChronoTimer()
{
}

void ChronoTimer::update() const
{
    if (m_paused || m_stopped)
    {
        return;
    }

    m_current = clock::now();
}

bool ChronoTimer::paused() const
{
    return m_paused;
}

bool ChronoTimer::stopped() const
{
    return m_stopped;
}

void ChronoTimer::start()
{
    if (!m_paused && !m_stopped)
    {
        return;
    }

    if (!m_stopped && m_paused)
    {
        m_paused = false;

        return;
    }

    if (m_stopped)
    {
       m_stopped = false;
       m_paused = false;
       m_start = clock::now();
    }
}

void ChronoTimer::pause()
{
    if (m_paused)
        return;

    m_current = clock::now();
    m_paused = true;
}

void ChronoTimer::stop()
{
    m_stopped = true;
}

ChronoTimer::nano ChronoTimer::elapsed() const
{
    if (m_auto)
    {
        update();
    }

    return m_current - m_start;
}

void ChronoTimer::setAutoUpdating(const bool autoUpdate)
{
    m_auto = autoUpdate;
}

bool ChronoTimer::autoUpdating() const
{
    return m_auto;
}
