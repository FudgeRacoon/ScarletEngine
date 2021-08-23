#include "scarlet/core/time/Timer.hpp"
using namespace scarlet;

void Timer::Start()
{
    this->startTime = HighResClock::now();
}
void Timer::Reset()
{
    this->startTime = HighResClock::now();
}

double Timer::EvaluateInSeconds()
{
    Seconds elapsed = std::chrono::duration_cast<Seconds>(
        HighResClock::now() - this->startTime
    );

    return elapsed.count();
}
double Timer::EvaluateInMilliSeconds()
{
    MilliSeconds elapsed = std::chrono::duration_cast<MilliSeconds>(
        HighResClock::now() - this->startTime
    );

    return elapsed.count();
}
int64 Timer::EvaluateInNanoSeconds()
{
    NanoSeconds elapsed = std::chrono::duration_cast<NanoSeconds>(
        HighResClock::now() - this->startTime
    );

    return elapsed.count();
}