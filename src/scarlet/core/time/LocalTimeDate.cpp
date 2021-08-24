#include "scarlet/core/time/LocalTimeDate.hpp"
using namespace scarlet;

LocalTimeDate::LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day)
{
    this->seconds = rawTimeInfo.tm_sec;
    this->minutes = rawTimeInfo.tm_min;
    this->hours = rawTimeInfo.tm_hour;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours)
{
    this->seconds = rawTimeInfo.tm_sec;
    this->minutes = rawTimeInfo.tm_min;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours), minutes(minutes)
{
    this->seconds = rawTimeInfo.tm_sec;
}
LocalTimeDate::LocalTimeDate(tm rawTimeInfo, uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds)
    :rawTimeInfo(rawTimeInfo), year(year), month(month), day(day), hours(hours), minutes(minutes), seconds(seconds) {}

uint32 LocalTimeDate::GetSeconds()
{
    return this->seconds;
}
uint32 LocalTimeDate::GetMinutes()
{
    return this->minutes;
}
uint32 LocalTimeDate::GetHours()
{
    return this->hours;
}
uint32 LocalTimeDate::GetDay()
{
    return this->day;
}
uint32 LocalTimeDate::GetMonth()
{
    return this->month;
}
uint32 LocalTimeDate::GetYear()
{
    return this->year;
}

LocalTimeDate LocalTimeDate::GetCurrentDate()
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);
 
    return LocalTimeDate(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday
    );
}
LocalTimeDate LocalTimeDate::GetCustomDate(uint32 year, uint32 month, uint32 day)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;
    rawTimeInfo->tm_min = minutes;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour,
        rawTimeInfo->tm_min 
    );

    return date;
}
LocalTimeDate LocalTimeDate::GetCustomDate(uint32 year, uint32 month, uint32 day, uint32 hours, uint32 minutes, uint32 seconds)
{
    time_t rawTime;
    tm* rawTimeInfo;

    time(&rawTime);
    rawTimeInfo = localtime(&rawTime);

    rawTimeInfo->tm_year = year;
    rawTimeInfo->tm_mon = month;
    rawTimeInfo->tm_mday = day;
    rawTimeInfo->tm_hour = hours;
    rawTimeInfo->tm_min = minutes;
    rawTimeInfo->tm_sec = seconds;

    LocalTimeDate date(
        *rawTimeInfo,
        rawTimeInfo->tm_year + 1900,
        rawTimeInfo->tm_mon + 1,
        rawTimeInfo->tm_mday,
        rawTimeInfo->tm_hour,
        rawTimeInfo->tm_min,
        rawTimeInfo->tm_sec 
    );

    return date;
}

const char* LocalTimeDate::Format(DateTimeFormat format)
{
    const char* specifier;
    switch(format)
    {
        case SCARLET_12_HH_MM_SS:       specifier = "%I:%M:%S %p"; break;
        case SCALRET_24_HH_MM:          specifier = "%H:%M"; break;
        case SCARLET_24_HH_MM_SS:       specifier = "%H:%M:%S"; break;

        case SCARLET_MM_DD_YY:          specifier = "%m/%d/%y"; break;
        case SCARLET_YYYY_MM_DD:        specifier = "%Y-%m-%d"; break;
        
        case SCARLET_FULL_WEEK:         specifier = "%A"; break;
        case SCARLET_ABBREVIATED_WEEK:  specifier = "%a"; break;
        
        case SCARLET_FULL_MONTH:        specifier = "%B"; break;
        case SCARLET_ABBREVIATED_MONTH: specifier = "%b"; break;
        
        case SCARLET_FULL_DATE_TIME:    specifier = "%c"; break;
    }

    char* buffer = new char[32];
    buffer[31] = '\0';

    strftime(buffer, 32, specifier, &this->rawTimeInfo);
    return buffer;
}
