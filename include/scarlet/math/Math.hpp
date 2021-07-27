#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <limits>
#include <math.h>

#include "scarlet/common/Types.hpp"

namespace scarlet
{   
    #define FLOAT_EQUAL(a, b) return a - b < Math::Epsilon ? true : false

    class Math
    {
    public:
        static constexpr float PI = 3.14159265359;
        static constexpr float Epsilon = std::numeric_limits<float>::epsilon();
        static constexpr uint64 Infinity = std::numeric_limits<uint64>::infinity();
    
    public:
        static float RadToDegree(float value)
        {
            return value * (180.0 / PI);
        }

        static float DegreeToRad(float value)
        {
            return value * (PI / 180.0);
        }

        static float Sin(float value)
        {
            return sin(value);
        }

        static float Cos(float value)
        {
            return cos(value);
        }

        static float Tan(float value)
        {
            return tan(value);
        }
    
        static float Asin(float value)
        {
            return asin(value);
        }

        static float Acos(float value)
        {
            return acos(value);
        }

        static float Atan2(float y, float x)
        {
            return atan2(y, x);
        }
    
        static float Sqrt(float value)
        {
            return sqrt(value);
        }
    
        static float Max(float a, float b)
        {
            return a > b ? a : b;
        }

        static float Min(float a, float b)
        {
            return a < b ? a : b;
        }

        static float Pow(float base, float exponent)
        {
            return powf(base, exponent);
        }

        static float Abs(float value)
        {
            return value < 0 ? -value : value;
        }

        static int Round(float value)
        {
            return (int)(value < 0.0f ? value - 0.5f : value + 0.5f);
        }
    
        static float Clamp(float value, float min, float max)
        {
            if(value > max)
                return max;
            if(value < min)
                return min;

            return value;
        }

        template <typename T>
        static void Swap(T* a, T* b)
        {
            T temp = *a;
            *a = *b;
            *b = temp;
        }
    };
}

#endif