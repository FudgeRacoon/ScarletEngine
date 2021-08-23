#ifndef LOGGERCONFIG_HPP
#define LOGGERCONFIG_HPP

namespace scarlet
{   
    enum LoggerConfig
    {
        SCARLET_ENABLE_LOGGER       = 1 << 0,   
        SCARLET_DISABLE_LOGGER      = 1 << 1,   
        SCARLET_ENABLE_FILE_OUTPUT  = 1 << 2,   
        SCARLET_DISABLE_FILE_OUTPUT = 1 << 3        
    };

    inline LoggerConfig operator |(LoggerConfig a, LoggerConfig b)
    {   
        return static_cast<LoggerConfig>(static_cast<int>(a) | static_cast<int>(b));
    }
}

#endif