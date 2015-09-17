
#pragma once

#include "ChronoTimer.h"

class CyclicTime
{
    using value_type = double;
public:
    CyclicTime(value_type secondsPerCycle);

	~CyclicTime();

	void update();

    value_type time() const;
    value_type normalizedTime() const;

    void start();
    void pause();
    void reset();
    void stop();

    value_type getSecondsPerCycle() const;
    void setSecondsPerCycle(value_type secondsPerCycle);

    bool isRunning() const;

protected:
    ChronoTimer m_timer;

    value_type m_secondsPerCycle;
    value_type m_current;
};
