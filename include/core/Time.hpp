#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <chrono>
#include "SDL2/SDL.h"
#include "core/math/Math.hpp"

namespace scarlet
{   
    struct TimePoint
    {
        uint32 second;
        uint32 minute;
        uint32 hour;
        uint32 day;
        uint32 month;
        uint32 year;
    };

    class Time
    {
    private:
        static float currentTime;
        static float previousTime;
        static float deltaTime;

    public:
        static constexpr float FRAME_RATE_TARGET = 60.0f;

    private:
        Time() = delete;
        ~Time() = delete;

    public:
        static void Reset();
        static void Update();

    public:
        static void CalculateLag();

    public:
        static TimePoint GetSystemTime();

    public:
        static float GetTicks();
        static float GetDeltaTime();
        static float GetFrameRate();
    };
}

#endif