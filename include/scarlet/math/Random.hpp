#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <stdlib.h>
#include <chrono>

#include "scarlet/math/Math.hpp"

namespace scarlet
{
    class Random
    {
    private:
        double min, max;

    public:
        Random()
        {
            srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

            this->min = 0;
            this->max = 100;
        }
        Random(double min, double max)
        {
            srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

            if(min > max)
            {
                double temp = min;
                this->min = max;
                this->max = temp;
            }
            else
            {
                this->min = min;
                this->max = max;
            }
        }
    
    public:
        double GetMin()
        {
            return this->min;
        }
        double GetMax()
        {
            return this->max;
        }

    public:
        void SetMin(double min)
        {
            this->min = min;
        }
        void SetMax(double max)
        {
            this->max = max;
        }

    public:
        int NextInt(int min, int max)
        {
            int num = min + rand() % (max - min + 1);
            return num;
        }
        int NextInt()
        {
            return this->NextInt((int)this->min, (int)this->max);
        }
    
    public:
        double NextFloat(double min, double max, int precision = 2)
        {
            double value;

            value = rand() % (int)Math::Pow(10, precision);

            value = min + (value / Math::Pow(10, precision)) * (max - min);

            return value;
        }
        double NextFloat(int precision = 2)
        {
            return this->NextFloat(this->min, this->max, precision);
        }
    };
}

#endif