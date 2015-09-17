#pragma once

#include <cstdint>
#include <chrono>

class ChronoTimer
{
    using clock = std::chrono::high_resolution_clock;
    using time_point = clock::time_point;
    using nano = std::chrono::duration<std::uint64_t, std::nano>;
public:
    ChronoTimer(
        bool start = true
    ,   bool autoUpdate = true);

    virtual ~ChronoTimer();

    nano elapsed() const;

    void setAutoUpdating(bool autoUpdate);
    bool autoUpdating() const;

    bool paused() const;
    bool stopped() const;

    void update() const;

    void start();
    void pause();
    void stop();

protected:
    bool m_paused;
    bool m_stopped;
    bool m_auto;

    time_point m_start;
    mutable time_point m_current;
};
