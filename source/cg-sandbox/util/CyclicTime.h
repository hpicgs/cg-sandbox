
#pragma once

#include <chrono>

#include "ChronoTimer.h"

enum class CyclingStatus : unsigned int
{
    TimeCycling
,   TimePausing
};

class CyclicTime
{
    using value_type = double;
public:
    CyclicTime(
        value_type time
    ,   value_type secondsPerCycle);

	~CyclicTime();

	void update();

    value_type time() const;
    value_type normalizedTime() const;

	void start(bool update = false);
	void pause(bool update = false);
    void reset(bool update = false);
    void stop (bool update = false);

    value_type getSecondsPerCycle() const;
    value_type setSecondsPerCycle(value_type secondsPerCycle);

    bool isRunning() const;

protected:
    void initialize();

    ChronoTimer::nano elapsed() const;
protected:
    ChronoTimer m_timer;
};
