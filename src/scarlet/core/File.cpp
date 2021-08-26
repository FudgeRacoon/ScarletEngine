#include "scarlet/core/File.hpp"
using namespace scarlet;

const char* File::GetName()
{
    return this->fileName;
}
size File::GetSize()
{
    SCARLET_CORE_ASSERT(this->fileStream.is_open() == true, "No file to do operations on.");

}

bool File::IsOpen()
{
    return this->fileStream.is_open();
}

void File::Open(const char* fileName)
{
    this->fileStream.open(fileName, std::ios::in | std::ios::out);

    if(this->fileStream.is_open())
        return;

    Logger::LogWarning("File does not exist.");
}
void File::Create(const char* fileName)
{
    this->fileStream.open(fileName, std::ios::in | std::ios::out);

    if(this->fileStream.is_open())
    {
        Logger::LogWarning("File already exists.");
        return;
    }

    this->fileStream.open(fileName, std::ios::out);
}
void File::Close()
{
    SCARLET_CORE_ASSERT(this->fileStream.is_open(), "No file to do operations on.");

    this->fileStream.close();
}
void File::Delete()
{
    SCARLET_CORE_ASSERT(this->fileStream.is_open(), "No file to do operations on.");

    remove(this->fileName);
}