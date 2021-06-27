#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <windows.h>
#include "core/Time.hpp"

namespace scarlet
{   
    class Logger
    {
    private:
        enum LogPriority
        {
            SCARLET_INFO = 14,
            SCARLET_DEBUG = 10,
            SCARLET_WARNING = 6,
            SCARLET_ERROR = 12,
            SCARLET_FATEL = 12
        };

    public:
        template <typename... Args>
        static void LogInfo(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_INFO);

            TimePoint timePoint = Time::GetSystemTime();

            printf("[INFO][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_DEBUG);

            TimePoint timePoint = Time::GetSystemTime();

            printf("[DEBUG][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_WARNING);

            TimePoint timePoint = Time::GetSystemTime();

            printf("[WARNING][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_ERROR);

            TimePoint timePoint = Time::GetSystemTime();

            printf("[ERROR][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_FATEL);

            TimePoint timePoint = Time::GetSystemTime();

            printf("[FATAL][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
    };
}

#endif