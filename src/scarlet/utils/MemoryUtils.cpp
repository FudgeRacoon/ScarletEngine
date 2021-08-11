#include "scarlet/utils/MemoryUtils.hpp"
using namespace scarlet;

void MemoryUtils::IntToBytes(void* dst, int value)
{
    int len = 4;
    int shiftamt = 24;
    
    byte* dstPtr = (byte*)dst;

    while(len > 0)
    {
        *dstPtr = value >> shiftamt;
        dstPtr++;
        len--;
        shiftamt -= 8;
    }
}
void MemoryUtils::IntToBytes(void* dst, uint32 value)
{
    int len = 4;
    int shiftamt = 24;
        
    byte* dstPtr = (byte*)dst;
    
    while(len > 0)
    {
        *dstPtr = value >> shiftamt;
        dstPtr++;
        len--;
        shiftamt -= 8;
    }
}

void MemoryUtils::MemorySet(void* dst, int value, size_t bytes)
{
    byte* dstPtr = (byte*)dst;

    for(int i = 0; i < bytes; i++)
        *(dstPtr + i) = (byte)value;
}
void MemoryUtils::MemoryCopy(void* dst, void* src, size_t bytes)
{
    byte* dstPtr = (byte*)dst;
    byte* srcPtr = (byte*)src;

    for(int i = 0; i < bytes; i++)
        *(dstPtr + i) = *(srcPtr + i);
}