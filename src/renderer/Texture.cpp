#include "core/renderer/Texture.hpp"
using namespace scarlet;

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
    
    this->buffer = new uint32[data->h * data->w];
    uint32* pixels = (uint32*)data->pixels;

    for(int y = 0; y < data->h; y++)
        for(int x = 0; x < data->w; x++)
            this->buffer[(y * data->w) + x] = pixels[(y * data->w) + x];

    this->width = data->w;
    this->height = data->h;

    int mode = data->format->BytesPerPixel;

    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, mode == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, this->buffer);

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