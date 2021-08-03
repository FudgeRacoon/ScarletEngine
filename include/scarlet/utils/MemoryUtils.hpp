#ifndef MEMORYUTILS_HPP
#define MEMORYUTILS_HPP

#include <stdlib.h>

#include "scarlet/common/Types.hpp"

namespace scarlet
{
    class MemoryUtils
    {
    public:
        static void IntToBytes(void* dst, int32 value);
        static void UintToBytes(void* dst, uint32 value);
    
    public:
        static void MemoryCopy(void* dst, void* src, size_t bytes);
    };
}

#endif