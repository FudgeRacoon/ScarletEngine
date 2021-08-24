#ifndef MEMORYUTILS_HPP
#define MEMORYUTILS_HPP

#include <stdlib.h>

#include "scarlet/core/Types.hpp"

namespace scarlet
{
    class MemoryUtils
    {
    public:
        static void IntToBytes(void* dst, int32 value);
        static void IntToBytes(void* dst, uint32 value);
    
    public:
        static void MemorySet(void* dst, int value, size bytes);
        static void MemoryCopy(void* dst, void* src, size bytes);
    };
}

#endif