#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <chrono>

#include "SDL2/SDL.h"

#include "core/Application.hpp"

#include "core/math/Math.hpp"

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
        static void Init();
        static void Update();
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