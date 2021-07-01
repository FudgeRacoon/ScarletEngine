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
        static double currentTime;
        static double previousTime;
        static double deltaTime;

    public:
        static constexpr double FRAME_RATE_TARGET = 240.0;

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
        static double GetTicks();
        static double GetDeltaTime();
        static double GetFrameRate();
    };
}

#endif