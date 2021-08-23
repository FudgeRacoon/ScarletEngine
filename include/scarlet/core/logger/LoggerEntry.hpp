#ifndef LOGGERENTRY_HPP
#define LOGGERENTRY_HPP

#include "../time/LocalTimeDate.hpp"

namespace scarlet
{
    enum LoggerPriority
    {
        SCARLET_INFO = 0,
        SCARLET_DEBUG,
        SCARLET_WARNING,
        SCARLET_ERROR,
        SCARLET_FATAL
    };

    struct LoggerEntry
    {
        const char* message;
        LocalTimeDate time;
        LoggerPriority priority;

        LoggerEntry(const char* message, LocalTimeDate time, LoggerPriority priority)
            : message(message), time(time), priority(priority) {}
        ~LoggerEntry() 
        {
            delete[] this->message;
        }
    };
}

#endif