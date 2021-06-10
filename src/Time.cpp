#include "core/Time.hpp"
#include "core/Logger.hpp"
using namespace scarlet;

float Time::currentTime  = 0.0f;
float Time::previousTime = 0.0f;
float Time::deltaTime = 0.0f;

void Time::Reset()
{
    previousTime = currentTime;
}
void Time::Update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - previousTime) * 0.001f;
}

void Time::CalculateLag()
{
    float lag = deltaTime - (1.0f / FRAME_RATE_TARGET);
    lag = lag * 1000.0f;

    if(lag >= 4.0f)
        Logger::LogWarning("%.2fms lag has occured.", lag);
}

float Time::GetTime()
{
    return SDL_GetTicks() * 0.001f;
}
float Time::GetDeltaTime()
{
    return deltaTime;
}
float Time::GetFrameRate()
{
    return 1.0f / deltaTime;
}