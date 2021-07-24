#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <chrono>

#include "SDL2/SDL.h"

#include "scarlet/core/Application.hpp"

#include "scarlet/common/Types.hpp"

using namespace std::chrono;

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
        static high_resolution_clock::time_point startTime;

    private:
        static double currentTime;
        static double previousTime;
        static double deltaTime;

    public:
        static constexpr double FRAME_RATE_TARGET = 240.0;

    private:
        Time() = delete;
        ~Time() = delete;

    private:
        static void Start();
        static void Elapsed();
        static void Reset();

    public:
        static double GetTicks();
        static double GetDeltaTime();
        static double GetFrameRate();
        static TimePoint GetSystemTime();

    friend Application;
    };
}

#endif