#include "core/Time.hpp"
#include "core/Logger.hpp"
using namespace scarlet;

high_resolution_clock::time_point Time::startTime;

double Time::currentTime  = 0.0;
double Time::previousTime = 0.0;
double Time::deltaTime = 0.0;

void Time::Init()
{
    startTime = high_resolution_clock::now();
}
void Time::Update()
{
    currentTime = GetTicks();
    deltaTime = currentTime - previousTime;
}
void Time::Reset()
{
    previousTime = currentTime;
}

double Time::GetTicks()
{
    duration<double, std::milli> elapsed = duration_cast<milliseconds>(
        high_resolution_clock::now() - startTime
    );
    
    return elapsed.count();
} 
double Time::GetDeltaTime()
{
    return deltaTime;
}
double Time::GetFrameRate()
{
    return 1000.0 / deltaTime;
}
TimePoint Time::GetSystemTime()
{
    system_clock::time_point currentSystemTime = system_clock::now();
    time_t c_currentSystemTime = system_clock::to_time_t(currentSystemTime);
    tm* timeStruct = localtime(&c_currentSystemTime);

    TimePoint timePoint
    {
        .second = timeStruct->tm_sec,
        .minute = timeStruct->tm_min,
        .hour   = timeStruct->tm_hour,
        .day    = timeStruct->tm_mday,
        .month  = timeStruct->tm_mon,
        .year   = timeStruct->tm_year + 1900
    };

    return timePoint;
} 