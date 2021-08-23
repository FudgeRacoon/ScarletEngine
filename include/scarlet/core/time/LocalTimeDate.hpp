#ifndef LocalTimeDate_HPP
#define LocalTimeDate_HPP

#include <time.h>
#include <string>

#include "../Types.hpp"

#include "DateTimeFormat.hpp"

namespace scarlet
{
    class LocalTimeDate
    {
    private:
        tm rawTimeInfo;

    private:
        uint32 seconds;
        uint32 minutes;
        uint32 hours;
        uint32 day;
        uint32 month;
        uint32 year;

    private:
        LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day);
        LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours);
        LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes);
        LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds);
    
    public:
        static LocalTimeDate GetCurrentDate();
        static LocalTimeDate GetCustomDate(uint32 year, uint32 month, uint32 day);
        static LocalTimeDate GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours);
        static LocalTimeDate GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes);
        static LocalTimeDate GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds);

    public:
        const char* Format(DateTimeFormat format);
    };
}

#endif