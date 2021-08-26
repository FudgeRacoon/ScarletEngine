#ifndef FILE_HPP
#define FILE_HPP

#include <stdio.h>
#include <fstream>

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"

namespace scarlet
{
    class File
    {
    private:
        const char* fileName;
        std::fstream fileStream;

    public:
        File() = default;

    public:
        const char* GetName();
        size GetSize();

    public:
        bool IsOpen();

    public:
        void Open(const char* fileName);
        void Create(const char* fileName);
        void Close();
        void Delete();

    public:
        void Write();
    };
}

#endif