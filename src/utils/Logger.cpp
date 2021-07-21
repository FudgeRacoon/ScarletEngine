#include "scarlet/utils/Logger.hpp"
using namespace scarlet;

std::vector<Logger::LogEntry> Logger::messages;

void Logger::CreateLogFile()
{
    std::fstream logFile("ScarletEngine.log", std::ios::out | std::ios::trunc);
    logFile << "----------Scarlet Engine Log File----------" << "\n\n";

    for(LogEntry message : messages)
    {
        const char* type;
        
        switch (message.type)
        {
            case LogPriority::SCARLET_INFO: type = "INFO"; break;
            case LogPriority::SCARLET_DEBUG: type = "DEBUG"; break;
            case LogPriority::SCARLET_WARNING: type = "WARNING"; break;
            case LogPriority::SCARLET_ERROR: type = "ERROR"; break;
            case LogPriority::SCARLET_FATAL: type = "FATAL"; break;
        }

        char buffer[256] = {'\0'};
        sprintf(buffer, "[%s][%02d:%02d:%02d]: %s\n", type, message.time.hour, message.time.minute, message.time.second, message.message);

        logFile.write(buffer, strlen(buffer)); 
    }

    logFile.close();
}