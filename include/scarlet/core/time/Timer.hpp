#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

#include "../Types.hpp"

namespace scarlet
{
    class Timer
    {
    using Seconds = std::chrono::duration<int64, std::ratio<1, 1>>;
    using MilliSeconds = std::chrono::duration<double, std::ratio<1, 1000>>;
    using NanoSeconds = std::chrono::duration<double, std::ratio<1, 1000000000>>;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HighResClock>;

    private:
        TimePoint startTime;

    public:
        Timer() = default;
        Timer(const Timer& other) = delete;
        Timer(const Timer&& other) = delete;

    public:
        void Start();
        void Reset();
    
    public:
        double EvaluateInSeconds();
        double EvaluateInMilliSeconds();
        int64 EvaluateInNanoSeconds();
    };
}

#endif