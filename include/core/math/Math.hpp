#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <limits>
#include <math.h>

#define FLOAT_EQUAL(a, b) return a - b < Math::Epsilon ? true : false;

namespace scarlet
{
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef unsigned long uint64;
    typedef float real;

    class Math
    {
    public:
        static constexpr real PI = 3.14159265359;
        static constexpr real Epsilon = std::numeric_limits<real>::epsilon();
        static constexpr uint64 Infinity = std::numeric_limits<uint64>::infinity();
    
    public:
        static real RadToDegree(real value)
        {
            return value * (180.0 / PI);
        }

        static real DegreeToRad(real value)
        {
            return value * (PI / 180.0);
        }

        static real Sin(real value)
        {
            return sin(value);
        }

        static real Cos(real value)
        {
            return cos(value);
        }

        static real Tan(real value)
        {
            return tan(value);
        }
    
        static real Asin(real value)
        {
            return asin(value);
        }

        static real Acos(real value)
        {
            return acos(value);
        }

        static real Atan2(real y, real x)
        {
            return atan2(y, x);
        }
    
        static real Sqrt(float value)
        {
            return sqrt(value);
        }
    
        static real Max(real a, real b)
        {
            return a > b ? a : b;
        }

        static real Min(real a, real b)
        {
            return a < b ? a : b;
        }

        static real Pow(real base, real exponent)
        {
            return powf(base, exponent);
        }

        static real Abs(real value)
        {
            return value < 0 ? -value : value;
        }

        static int Round(real value)
        {
            return (int)(value < 0.0f ? value - 0.5f : value + 0.5f);
        }
    
        static real Clamp(real value, real min, real max)
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