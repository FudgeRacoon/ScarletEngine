#include "core/Time.hpp"
#include "core/Logger.hpp"
using namespace scarlet;

double Time::currentTime  = 0.0;
double Time::previousTime = 0.0;
double Time::deltaTime = 0.0;

void Time::Reset()
{
    previousTime = currentTime;
}
void Time::Update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - previousTime) * 0.001;
}

void Time::CalculateLag()
{
    double lag = deltaTime - (1.0 / FRAME_RATE_TARGET);
    lag = lag * 1000.0;

    if(lag >= 4.0)
        Logger::LogWarning("%.2fms lag has occured.", lag);
}

TimePoint Time::GetSystemTime()
{
    std::chrono::system_clock::time_point chronoTimePoint = std::chrono::system_clock::now();
    time_t cTime = std::chrono::system_clock::to_time_t(chronoTimePoint);
    tm* cTimeStruct = localtime(&cTime);

    TimePoint timePoint
    {
        .second = cTimeStruct->tm_sec,
        .minute = cTimeStruct->tm_min,
        .hour = cTimeStruct->tm_hour,
        .day = cTimeStruct->tm_mday,
        .month = cTimeStruct->tm_mon,
        .year = cTimeStruct->tm_year + 1900
    };

    return timePoint;
} 

double Time::GetTicks()
{
    return SDL_GetTicks() * 0.001f;
} 
double Time::GetDeltaTime()
{
    return deltaTime;
}
double Time::GetFrameRate()
{
    return 1.0 / deltaTime;
}