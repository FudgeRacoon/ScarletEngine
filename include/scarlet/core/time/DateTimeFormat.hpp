#ifndef DATETIMEFORMAT_HPP
#define DATETIMEFORMAT_HPP

namespace scarlet
{
    enum DateTimeFormat
    {
        SCARLET_12_HH_MM_SS,
        SCALRET_24_HH_MM,
        SCARLET_24_HH_MM_SS,

        SCARLET_MM_DD_YY,
        SCARLET_YYYY_MM_DD,
        
        SCARLET_FULL_WEEK,
        SCARLET_ABBREVIATED_WEEK,
        
        SCARLET_FULL_MONTH,
        SCARLET_ABBREVIATED_MONTH,
        
        SCARLET_FULL_DATE_TIME
    };
}

#endif