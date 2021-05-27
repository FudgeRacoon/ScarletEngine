#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include "SDL2/SDL.h"

namespace scarlet
{
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
        static float GetTime();
        static float GetDeltaTime();
        static float GetFrameRate();
    };
}

#endif