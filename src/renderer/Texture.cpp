#include "core/renderer/Texture.hpp"
using namespace scarlet;

#include <string.h>

#include "core/Logger.hpp"
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Texture::Texture(const char* filepath)
{
    SDL_Surface* data = IMG_Load(filepath);
    if(!data)
    {
        Logger::LogError("Texture file does not exist.");
        return;
    }   
    
    this->buffer = new uint8[data->h * data->pitch];
    uint8* pixels = (uint8*)data->pixels;
    
    FlipTexture(pixels, data->w, data->h, data->format->BytesPerPixel);

    for(int y = 0; y < data->h; y++)
        for(int x = 0; x < data->pitch; x++)
            this->buffer[(y * data->pitch) + x] = pixels[(y * data->pitch) + x];

    this->width = data->w;
    this->height = data->h;

    int bytesPerPixel = data->format->BytesPerPixel; 

    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, bytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, this->buffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(data);
}
Texture::~Texture()
{
    glDeleteTextures(1, &this->ID);
}

int Texture::GetWidth()
{
    return this->width;
}
int Texture::GetHeight()
{
    return this->height;
}

void Texture::Bind(uint32 slot) const
{   
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::FlipTexture(uint8* pixels, int width, int height, int bytesPerPixel)
{   
    height -= 1;
    int pitch = bytesPerPixel * width;

    uint8* topPixels = pixels;
    uint8* bottomPixels = pixels + ((height) * pitch);

    for(int y = 0; y < height / 2; y++)
    {
        uint8* top = new uint8[pitch];
        uint8* bottom = new uint8[pitch];

        for(int x = 0; x < pitch; x++)
        {
            top[x] = topPixels[x];
            bottom[x] = bottomPixels[x];
        }

        for(int x = 0; x < pitch; x++)
        {
            pixels[(y * pitch) + x] = bottom[x];
            pixels[((height - y) * pitch) + x] = top[x];
        }

        topPixels += pitch;
        bottomPixels -= pitch;

        delete[] top;
        delete[] bottom;
    }
}