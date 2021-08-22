#include "scarlet/utils/Logger.hpp"
using namespace scarlet;

std::vector<Logger::LoggerEntry*> Logger::messages;
LoggerConfig Logger::configFlags = LoggerConfig::SCARLET_ENABLE_LOGGER | LoggerConfig::SCARLET_ENABLE_FILE_OUTPUT;

void Logger::CreateLogFile()
{
    if(STORE_VALID)
    {
        std::fstream logFile("ScarletEngine.log", std::ios::out | std::ios::trunc);
        logFile << "----------Scarlet Engine Log File----------" << "\n\n";

        for(LoggerEntry* message : messages)
        {
            const char* logType;
            switch (message->priority)
            {
                case LoggerPriority::SCARLET_INFO:    logType = "INFO"; break;
                case LoggerPriority::SCARLET_DEBUG:   logType = "DEBUG"; break;
                case LoggerPriority::SCARLET_WARNING: logType = "WARNING"; break;
                case LoggerPriority::SCARLET_ERROR:   logType = "ERROR"; break;
                case LoggerPriority::SCARLET_FATAL:   logType = "FATAL"; break;
            }

            char buffer[256] = {'\0'};
            sprintf(buffer, "[%s][%02d:%02d:%02d]: %s\n", logType, message->time.hour, message->time.minute, message->time.second, message->message);

            logFile.write(buffer, strlen(buffer)); 
        }

        logFile.close();
    }
}

void Logger::OnInit()
{

}
void Logger::OnShutDown()
{
    messages.clear();
}

void Logger::Configure(LoggerConfig flags)
{
    configFlags = flags;
}