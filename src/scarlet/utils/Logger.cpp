#include "scarlet/utils/Logger.hpp"
using namespace scarlet;

std::vector<Logger::LoggerEntry> Logger::messages;
LoggerConfig_Flags Logger::configFlags = LoggerConfig_Flags::ENABLE_LOGGER | LoggerConfig_Flags::ENABLE_FILE_OUTPUT;

void Logger::Configure(LoggerConfig_Flags flags)
{
    configFlags = flags;
}

void Logger::CreateLogFile()
{
    if((int)configFlags == (int)(ENABLE_LOGGER | ENABLE_FILE_OUTPUT))
    {
        std::fstream logFile("ScarletEngine.log", std::ios::out | std::ios::trunc);
        logFile << "----------Scarlet Engine Log File----------" << "\n\n";

        for(LoggerEntry message : messages)
        {
            const char* type;
            
            switch (message.type)
            {
                case LoggerPriority::SCARLET_INFO:    type = "INFO"; break;
                case LoggerPriority::SCARLET_DEBUG:   type = "DEBUG"; break;
                case LoggerPriority::SCARLET_WARNING: type = "WARNING"; break;
                case LoggerPriority::SCARLET_ERROR:   type = "ERROR"; break;
                case LoggerPriority::SCARLET_FATAL:   type = "FATAL"; break;
            }

            char buffer[256] = {'\0'};
            sprintf(buffer, "[%s][%02d:%02d:%02d]: %s\n", type, message.time.hour, message.time.minute, message.time.second, message.message);

            logFile.write(buffer, strlen(buffer)); 
        }

        logFile.close();
    }
}