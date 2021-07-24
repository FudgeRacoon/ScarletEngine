#ifndef COLOR_HPP
#define COLOR_HPP

#include "scarlet/common/Types.hpp"

#include "scarlet/math/Math.hpp"

namespace scarlet
{
    class Color
    {
    public:
        byte r;
        byte g;
        byte b;
        byte a;

    public:
        Color()
        {
            this->r = 255;
            this->g = 255;
            this->b = 255;
            this->a = 255;
        }
        Color(float r, float g, float b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = 255;
        }
        Color(float r, float g, float b, float a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

    public:
        static Color RED() 
        {
            return Color(255, 0, 0);
        }
        static Color GREEN() 
        {
            return Color(0, 255, 0);
        }
        static Color BLUE() 
        {
            return Color(0, 0, 255);
        }
        static Color BLACK() 
        {
            return Color(0, 0, 0);
        }

    public:
        Color operator +(Color c)
        {
            Color result;

            result.r = Math::Clamp(this->r + c.r, 0, 255);
            result.g = Math::Clamp(this->g + c.g, 0, 255);
            result.b = Math::Clamp(this->b + c.b, 0, 255);

            return result;
        }
        Color operator -(Color c)
        {
            Color result;

            result.r = Math::Clamp(this->r - c.r, 0, 255);
            result.g = Math::Clamp(this->g - c.g, 0, 255);
            result.b = Math::Clamp(this->b - c.b, 0, 255);

            return result;
        }
        Color operator *(Color c)
        {
            Color result;

            result.r = Math::Clamp(this->r * c.r, 0, 255);
            result.g = Math::Clamp(this->g * c.g, 0, 255);
            result.b = Math::Clamp(this->b * c.b, 0, 255);

            return result;
        }
        Color operator *(float value)
        {
            Color result;

            result.r = Math::Clamp(this->r * value, 0, 255);
            result.g = Math::Clamp(this->g * value, 0, 255);
            result.b = Math::Clamp(this->b * value, 0, 255);

            return result;
        }
        bool operator ==(Color c)
        {
            return this->r == c.r &&
                   this->g == c.g &&
                   this->b == c.b &&
                   this->a == c.a;
        }
        bool operator !=(Color c)
        {
            return this->r != c.r &&
                   this->g != c.g &&
                   this->b != c.b &&
                   this->a != c.a;
        }
        
    public:
        static Color Lerp(Color c1, Color c2, float t)
        {
            return Color
            (
                c1.r +( (c2.r - c1.r) * t),
                c1.g +( (c2.g - c1.g) * t),
                c1.b +( (c2.b - c1.b) * t),
                c1.a +( (c2.a - c1.a) * t)
            );
        }
    
    public:
        static uint32 RGBToHex(Color c)
        {
            return c.r << 24 | c.g << 16 | c.b << 8 | c.a;
        }
        static Color HexToRGB(uint32 value)
        {
            Color color;

            color.r = value >> 24;
            color.g = value >> 16;
            color.b = value >> 8;
            color.a = value;

            return color;
        }
    };
}

#endif