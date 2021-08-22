#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

#include "scarlet/core/Application.hpp"

#include "scarlet/utils/Time.hpp"
#include "scarlet/utils/Logger/Base.hpp"
#include "scarlet/utils/Logger/LoggerEntry.hpp"
#include "scarlet/utils/Logger/LoggerConfig.hpp"

namespace scarlet
{
    class Logger
    {
    private:
        static LoggerConfig configFlags;
        static std::vector<LoggerEntry*> messages;

    private:
        static void CreateLogFile();

    private:
        template <typename... Args>
        static void PrintString(LoggerPriority priority, const char* message, Args... args)
        {
            switch (priority)
            {
                case SCARLET_INFO :    
                {
                    if(PRINT_VALID)
                    {
                        TimePoint timePoint = Time::GetSystemTime();

                        printf("\033[34m");
                        printf("[INFO][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");
                    }

                    break;
                }
                case SCARLET_DEBUG :   
                {
                    if(PRINT_VALID)
                    {
                        TimePoint timePoint = Time::GetSystemTime();

                        printf("\033[33m");
                        printf("[DEBUG][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");
                    }

                    break;
                }
                case SCARLET_WARNING : 
                {
                    if(PRINT_VALID)
                    {
                        TimePoint timePoint = Time::GetSystemTime();

                        printf("\033[32m");
                        printf("[WARNING][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");
                    }

                    break;
                }
                case SCARLET_ERROR :   
                {
                    if(PRINT_VALID)
                    {
                        TimePoint timePoint = Time::GetSystemTime();

                        printf("\033[91m");
                        printf("[ERROR][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");
                    }

                    break;
                }
                case SCARLET_FATAL :   
                {
                    if(PRINT_VALID)
                    {
                        TimePoint timePoint = Time::GetSystemTime();

                        printf("\033[31m");
                        printf("[FATAL][%02d:%02d:%02d]: ", timePoint.hour, timePoint.minute, timePoint.second);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");
                    }

                    break;
                }
            }
        }
        template <typename... Args>
        static void StoreString(LoggerPriority priority, const char* message, Args... args)
        {
            if(STORE_VALID)
            {
                int size = strlen(message);
                char* buffer = new char[size + 1];
                buffer[size] = '\0';
                
                sprintf(buffer, message, args...);

                messages.push_back(new LoggerEntry(buffer, Time::GetSystemTime(), priority));
            }
        }

    public:
        static void OnInit();
        static void OnShutDown();

    public:
        static void Configure(LoggerConfig flags);
    
    public:
        template <typename... Args>
        static void LogInfo(const char* message, Args... args)
        {
            PrintString(LoggerPriority::SCARLET_INFO, message, args...);   
            StoreString(LoggerPriority::SCARLET_INFO, message, args...);
        }
        template <typename... Args>
        static void LogDebug(const char* message, Args... args)
        {
            PrintString(LoggerPriority::SCARLET_DEBUG, message, args...);
            StoreString(LoggerPriority::SCARLET_DEBUG, message, args...);
        }
        template <typename... Args>
        static void LogWarning(const char* message, Args... args)
        {
            PrintString(LoggerPriority::SCARLET_WARNING, message, args...);
            StoreString(LoggerPriority::SCARLET_WARNING, message, args...);
        }
        template <typename... Args>
        static void LogError(const char* message, Args... args)
        {
            PrintString(LoggerPriority::SCARLET_ERROR, message, args...);
            StoreString(LoggerPriority::SCARLET_ERROR, message, args...);
        }   
        template <typename... Args>
        static void LogFatal(const char* message, Args... args)
        {
            PrintString(LoggerPriority::SCARLET_FATAL, message, args...);
            StoreString(LoggerPriority::SCARLET_FATAL, message, args...);
        }
    
    friend Application;
    };
}

#endif