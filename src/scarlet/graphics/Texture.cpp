#include "scarlet/graphics/Texture.hpp"
using namespace scarlet;

Texture::Texture(const char* filepath)
{
    SDL_Surface* data = IMG_Load(filepath);
    if(!data)
    {
        Logger::LogError("Texture file does not exist.");
        return;
    }   

    byte* pixels = (byte*)data->pixels;
    byte* textureData = new byte[data->h * data->pitch];
    
    for(int y = 0; y < data->h; y++)
        for(int x = 0; x < data->pitch; x++)
            textureData[(y * data->pitch) + x] = pixels[(y * data->pitch) + x];

    this->width = data->w;
    this->height = data->h;
    this->bytesPerPixel = data->format->BytesPerPixel; 

    byte* topPixels = textureData;
    byte* bottomPixels = textureData + ((this->height - 1) * data->pitch);

    for(int y = 0; y < this->height / 2; y++)
    {
        byte* tempTopBuffer = new byte[data->pitch];
        byte* tempBottomBuffer = new byte[data->pitch];

        MemoryUtils::MemoryCopy(tempTopBuffer, topPixels, data->pitch);
        MemoryUtils::MemoryCopy(tempBottomBuffer, bottomPixels, data->pitch);

        MemoryUtils::MemoryCopy(topPixels, tempBottomBuffer, data->pitch);
        MemoryUtils::MemoryCopy(bottomPixels, tempTopBuffer, data->pitch);

        topPixels += data->pitch;
        bottomPixels -= data->pitch;

        delete[] tempTopBuffer;
        delete[] tempBottomBuffer;
    }

    GLCALL(glGenTextures(1, &this->textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->textureId));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, this->bytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, textureData));

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    delete[] textureData;
    SDL_FreeSurface(data);
}
Texture::Texture(uint32 color, uint32 width, uint32 height)
{
    uint32 pitch = width * 4;
    byte* textureData = new byte[height * pitch];
    
    for(int y = 0; y < height; y++)
        for(int x = 0; x < pitch; x += 4)
            MemoryUtils::IntToBytes(textureData + ((y * pitch) + x), color);

    this->width = width;
    this->height = height;
    this->bytesPerPixel = 4;

    GLCALL(glGenTextures(1, &this->textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->textureId));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData));

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    delete[] textureData;
}
Texture::Texture(void* pixels, uint32 width, uint32 height)
{
    uint32 pitch = width * 4;
    byte* textureData = new byte[height * pitch];
    
    byte* otherPixels = (byte*)pixels;
    
    for(int y = 0; y < height; y++)
        for(int x = 0; x < pitch; x++)
            textureData[(y * pitch) + x] = otherPixels[(y * pitch) + x];

    this->width = width;
    this->height = height;
    this->bytesPerPixel = 4;

    byte* topPixels = textureData;
    byte* bottomPixels = textureData + ((this->height - 1) * pitch);

    for(int y = 0; y < this->height / 2; y++)
    {
        byte* tempTopBuffer = new byte[pitch];
        byte* tempBottomBuffer = new byte[pitch];

        MemoryUtils::MemoryCopy(tempTopBuffer, topPixels, pitch);
        MemoryUtils::MemoryCopy(tempBottomBuffer, bottomPixels, pitch);

        MemoryUtils::MemoryCopy(topPixels, tempBottomBuffer, pitch);
        MemoryUtils::MemoryCopy(bottomPixels, tempTopBuffer, pitch);

        topPixels += pitch;
        bottomPixels -= pitch;

        delete[] tempTopBuffer;
        delete[] tempBottomBuffer;
    }

    GLCALL(glGenTextures(1, &this->textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->textureId));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData));

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    delete[] textureData;
}
Texture::~Texture()
{
   GLCALL(glDeleteTextures(1, &this->textureId));
}

uint32 Texture::GetId()
{
    return this->textureId;
}
int Texture::GetWidth()
{
    return this->width;
}
int Texture::GetHeight()
{
    return this->height;
}
int Texture::GetBytesPerPixel()
{
    return this->bytesPerPixel;
}

void Texture::Bind(uint32 slot) const
{   
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->textureId));
}
void Texture::UnBind() const
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}