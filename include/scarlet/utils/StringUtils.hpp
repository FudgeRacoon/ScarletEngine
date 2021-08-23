#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <math.h>
#include <string>

#include "scarlet/core/Types.hpp"

namespace scarlet
{
    class StringUtils
    {
    public:
        static uint64 HashCode(std::string string);
    };
}

#endif