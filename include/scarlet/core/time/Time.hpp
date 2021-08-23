#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <chrono>

#include "../Application.hpp"
#include "../Types.hpp"

namespace scarlet
{
    class Time
    {
    using NanoSeconds = std::chrono::duration<int64, std::ratio<1, 1000000000>>;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HighResClock>;

    private:
        static TimePoint startTime;
        static TimePoint currentTime;
        static TimePoint previousTime;

    private:
        static float timeScale;
        static double deltaTime;
        static double elapsedTime;
        static double elapsedUnscaledTime;

    private:
        Time() = delete;
        ~Time() = delete;

    private:
        static void OnInit();
        static void OnUpdate();
        static void OnFrameEnd();

    public:
        static float GetTimeScale();
        static double GetFrameRate();
        static double GetDeltaTime();
        static double GetElapsedTime();
        static double GetElapsedUnscaledTime();

    public:
        static void SetTimeScale(float value);

    friend Application;
    };
}

#endif