#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

#include "../time/LocalTimeDate.hpp"

#include "Base.hpp"
#include "LoggerEntry.hpp"
#include "LoggerConfig.hpp"

namespace scarlet
{
    class Logger
    {
    private:
        static LoggerConfig configFlags;
        static std::vector<LoggerEntry*> messages;
    
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
                        LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                        const char* buffer = date.Format(DateTimeFormat::SCARLET_24_HH_MM_SS);

                        printf("\033[34m");
                        printf("[INFO][%s]: ", buffer);
                        printf(message, args...);
                        printf("\n");  
                        printf("\033[0m");

                        delete[] buffer;
                    }

                    break;
                }
                case SCARLET_DEBUG :   
                {
                    if(PRINT_VALID)
                    {
                        LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                        const char* buffer = date.Format(DateTimeFormat::SCARLET_24_HH_MM_SS);

                        printf("\033[33m");
                        printf("[DEBUG][%s]: ", buffer);
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
                        LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                        const char* buffer = date.Format(DateTimeFormat::SCARLET_24_HH_MM_SS);

                        printf("\033[32m");
                        printf("[WARNING][%s]: ", buffer);
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
                        LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                        const char* buffer = date.Format(DateTimeFormat::SCARLET_24_HH_MM_SS);

                        printf("\033[91m");
                        printf("[ERROR][%s]: ", buffer);
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
                        LocalTimeDate date = LocalTimeDate::GetCurrentDate();
                        const char* buffer = date.Format(DateTimeFormat::SCARLET_24_HH_MM_SS);

                        printf("\033[31m");
                        printf("[FATAL][%s]: ", buffer);
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

                messages.push_back(new LoggerEntry(buffer, LocalTimeDate::GetCurrentDate(), priority));
            }
        }

    public:
        static void OnInit();
        static void OnShutDown();

    public:
        static void CreateLogFile();
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
    };
}

#endif