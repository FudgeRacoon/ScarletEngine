#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>

#include "scarlet/utils/Time.hpp"

namespace scarlet
{   
    enum LoggerConfig_Flags
    {
        ENABLE_LOGGER       = 1 << 0,   
        DISABLE_LOGGER      = 1 << 1,   
        ENABLE_FILE_OUTPUT  = 1 << 2,   
        DISABLE_FILE_OUTPUT = 1 << 3        
    };

    inline LoggerConfig_Flags operator |(LoggerConfig_Flags a, LoggerConfig_Flags b)
    {   
        return static_cast<LoggerConfig_Flags>(static_cast<int>(a) | static_cast<int>(b));
    }

    class Logger
    {
    private:
        enum LoggerPriority
        {
            SCARLET_INFO = 0,
            SCARLET_DEBUG,
            SCARLET_WARNING,
            SCARLET_ERROR,
            SCARLET_FATAL
        };

    private:
        struct LoggerEntry
        {
            LoggerPriority type;
            TimePoint time;
            const char* message;
        };

    private:
        static LoggerConfig_Flags configFlags;
        static std::vector<LoggerEntry> messages;

    public:
        template <typename... Args>
        static void LogInfo(const char* message, Args... args)
        {
            if((int)configFlags == (int)ENABLE_LOGGER       || 
               (int)configFlags == (int)DISABLE_FILE_OUTPUT || 
               (int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
            {
                TimePoint timePoint = Time::GetSystemTime();

                printf("\033[38;2;100;255;100m");
                printf("[INFO][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                printf(message, args...);
                printf("\n");  
                printf("\033[0m");

                if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
                {
                    int size = strlen(message);
                    char* buffer = new char[size + 1];
                    buffer[size] = '\0';
                    
                    sprintf(buffer, message, args...);

                    LoggerEntry LoggerEntry;
                    LoggerEntry.type = LoggerPriority::SCARLET_INFO;
                    LoggerEntry.time = timePoint;
                    LoggerEntry.message = buffer;
                    
                    messages.push_back(LoggerEntry);
                }
            }
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            if((int)configFlags == (int)ENABLE_LOGGER       || 
               (int)configFlags == (int)DISABLE_FILE_OUTPUT || 
               (int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
            {
                TimePoint timePoint = Time::GetSystemTime();

                printf("\033[38;2;0;255;0m");
                printf("[DEBUG][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                printf(message, args...);
                printf("\n");
                printf("\033[0m");

                if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
                {
                    int size = strlen(message);
                    char* buffer = new char[size + 1];
                    buffer[size] = '\0';

                    sprintf(buffer, message, args...);

                    LoggerEntry LoggerEntry;
                    LoggerEntry.type = LoggerPriority::SCARLET_DEBUG;
                    LoggerEntry.time = timePoint;
                    LoggerEntry.message = buffer;

                    messages.push_back(LoggerEntry);
                }
            }
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            if((int)configFlags == (int)ENABLE_LOGGER       || 
               (int)configFlags == (int)DISABLE_FILE_OUTPUT || 
               (int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
            {
                TimePoint timePoint = Time::GetSystemTime();

                printf("\033[38;2;255;100;100m");
                printf("[WARNING][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                printf(message, args...);
                printf("\n");
                printf("\033[0m");

                if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
                {
                    int size = strlen(message);
                    char* buffer = new char[size + 1];
                    buffer[size] = '\0';

                    sprintf(buffer, message, args...);

                    LoggerEntry LoggerEntry;
                    LoggerEntry.type = LoggerPriority::SCARLET_WARNING;
                    LoggerEntry.time = timePoint;
                    LoggerEntry.message = buffer;

                    messages.push_back(LoggerEntry);
                }
            }
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            if((int)configFlags == (int)ENABLE_LOGGER       || 
               (int)configFlags == (int)DISABLE_FILE_OUTPUT || 
               (int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
            {
                TimePoint timePoint = Time::GetSystemTime();

                printf("\033[38;2;255;50;50m");
                printf("[ERROR][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                printf(message, args...);
                printf("\n");
                printf("\033[0m");

                if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
                {
                    int size = strlen(message);
                    char* buffer = new char[size + 1];
                    buffer[size] = '\0';

                    sprintf(buffer, message, args...);

                    LoggerEntry LoggerEntry;
                    LoggerEntry.type = LoggerPriority::SCARLET_ERROR;
                    LoggerEntry.time = timePoint;
                    LoggerEntry.message = buffer;

                    messages.push_back(LoggerEntry);
                }
            }
        }   
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            if((int)configFlags == (int)ENABLE_LOGGER       || 
               (int)configFlags == (int)DISABLE_FILE_OUTPUT || 
               (int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
            {
                TimePoint timePoint = Time::GetSystemTime();

                printf("\033[38;2;255;0;0m");
                printf("[FATAL][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                printf(message, args...);
                printf("\n");
                printf("\033[0m");

                if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
                {
                    int size = strlen(message);
                    char* buffer = new char[size + 1];
                    buffer[size] = '\0';

                    sprintf(buffer, message, args...);

                    LoggerEntry LoggerEntry;
                    LoggerEntry.type = LoggerPriority::SCARLET_FATAL;
                    LoggerEntry.time = timePoint;
                    LoggerEntry.message = buffer;

                    messages.push_back(LoggerEntry);
                }
            }
        }
    
    public:
        static void CreateLogFile();
        static void Configure(LoggerConfig_Flags flags);
    };
}

#endif