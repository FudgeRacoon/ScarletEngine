#include "scarlet/core/time/Time.hpp"
using namespace scarlet;

Time::TimePoint Time::startTime;
Time::TimePoint Time::currentTime;
Time::TimePoint Time::previousTime;

double Time::deltaTime = 0.0;
double Time::elapsedTime = 0.0;
double Time::elapsedUnscaledTime = 0.0f;

float Time::timeScale = 1.0f;

void Time::OnInit()
{
    startTime = HighResClock::now();
    currentTime = HighResClock::now();
    previousTime = HighResClock::now();
}
void Time::OnUpdate()
{
    deltaTime = 0.0;

    if(timeScale > 0.0f)
    {
        currentTime = HighResClock::now();

        NanoSeconds delta = std::chrono::duration_cast<NanoSeconds>(currentTime - previousTime);
        NanoSeconds elapsed = std::chrono::duration_cast<NanoSeconds>(currentTime - startTime);

        deltaTime = delta.count() * (1e-9) * timeScale;
        elapsedTime += deltaTime;
        elapsedUnscaledTime = elapsed.count() * (1e-9);
    }
}
void Time::OnFrameEnd()
{
    previousTime = currentTime;
}

double Time::GetFrameRate()
{
    return 1.0 / deltaTime;
}
double Time::GetDeltaTime()
{
    return deltaTime;
}
double Time::GetElapsedTime()
{
    return elapsedTime;
}
double Time::GetElapsedUnscaledTime()
{
    return elapsedUnscaledTime;
}