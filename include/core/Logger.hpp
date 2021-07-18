#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>


#include "core/Time.hpp"

namespace scarlet
{   
    class Logger
    {
    private:
        enum LogPriority
        {
            SCARLET_INFO,
            SCARLET_DEBUG,
            SCARLET_WARNING,
            SCARLET_ERROR,
            SCARLET_FATAL
        };

        struct LogEntry
        {
            LogPriority type;
            TimePoint time;
            const char* message;
        };

    private:
        static std::vector<LogEntry> messages;

    public:
        template <typename... Args>
        static void LogInfo(const char* message, Args... args)
        {
            TimePoint timePoint = Time::GetSystemTime();

            printf("\033[38;2;100;255;100m");
            printf("[INFO][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");  
            printf("\033[0m");

            int size = strlen(message);
            char* buffer = new char[size + 1];
            buffer[size] = '\0';
            
            sprintf(buffer, message, args...);

            LogEntry logEntry;
            logEntry.type = LogPriority::SCARLET_INFO;
            logEntry.time = timePoint;
            logEntry.message = buffer;
            
            messages.push_back(logEntry);
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            TimePoint timePoint = Time::GetSystemTime();

            printf("\033[38;2;0;255;0m");
            printf("[DEBUG][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            printf("\033[0m");

            int size = strlen(message);
            char* buffer = new char[size + 1];
            buffer[size] = '\0';

            sprintf(buffer, message, args...);

            LogEntry logEntry;
            logEntry.type = LogPriority::SCARLET_DEBUG;
            logEntry.time = timePoint;
            logEntry.message = buffer;
            
            messages.push_back(logEntry);
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            TimePoint timePoint = Time::GetSystemTime();

            printf("\033[38;2;255;100;100m");
            printf("[WARNING][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            printf("\033[0m");

            int size = strlen(message);
            char* buffer = new char[size + 1];
            buffer[size] = '\0';

            sprintf(buffer, message, args...);

            LogEntry logEntry;
            logEntry.type = LogPriority::SCARLET_WARNING;
            logEntry.time = timePoint;
            logEntry.message = buffer;
            
            messages.push_back(logEntry);
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            TimePoint timePoint = Time::GetSystemTime();

            printf("\033[38;2;255;50;50m");
            printf("[ERROR][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            printf("\033[0m");

            int size = strlen(message);
            char* buffer = new char[size + 1];
            buffer[size] = '\0';

            sprintf(buffer, message, args...);

            LogEntry logEntry;
            logEntry.type = LogPriority::SCARLET_ERROR;
            logEntry.time = timePoint;
            logEntry.message = buffer;
            
            messages.push_back(logEntry);
        }
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            TimePoint timePoint = Time::GetSystemTime();

            printf("\033[38;2;255;0;0m");
            printf("[FATAL][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
            printf(message, args...);
            printf("\n");
            printf("\033[0m");

            int size = strlen(message);
            char* buffer = new char[size + 1];
            buffer[size] = '\0';
            
            sprintf(buffer, message, args...);

            LogEntry logEntry;
            logEntry.type = LogPriority::SCARLET_FATAL;
            logEntry.time = timePoint;
            logEntry.message = buffer;
            
            messages.push_back(logEntry);
        }
    
    public:
        static void CreateLogFile();
    };
}

#endif