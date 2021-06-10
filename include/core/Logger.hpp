#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <chrono>
#include <time.h>
#include <windows.h>
using std::chrono::system_clock;

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

            system_clock::time_point currentTime = system_clock::now();
            time_t tt = system_clock::to_time_t(currentTime);
            struct tm* timeInfo = localtime(&tt);

            printf("[INFO][%d:%d:%d]: ", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_DEBUG);

            system_clock::time_point currentTime = system_clock::now();
            time_t tt = system_clock::to_time_t(currentTime);
            struct tm* timeInfo = localtime(&tt);

            printf("[DEBUG][%d:%d:%d]: ", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_WARNING);

            system_clock::time_point currentTime = system_clock::now();
            time_t tt = system_clock::to_time_t(currentTime);
            struct tm* timeInfo = localtime(&tt);

            printf("[WARNING][%d:%d:%d]: ", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_ERROR);

            system_clock::time_point currentTime = system_clock::now();
            time_t tt = system_clock::to_time_t(currentTime);
            struct tm* timeInfo = localtime(&tt);

            printf("[ERROR][%d:%d:%d]: ", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (int)LogPriority::SCARLET_FATEL);

            system_clock::time_point currentTime = system_clock::now();
            time_t tt = system_clock::to_time_t(currentTime);
            struct tm* timeInfo = localtime(&tt);

            printf("[FATAL][%d:%d:%d]: ", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
            printf(message, args...);
            printf("\n");
            
            SetConsoleTextAttribute(hConsole, 7);
        }
    };
}

#endif