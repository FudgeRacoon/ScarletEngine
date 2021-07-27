#include "scarlet/graphics/Texture.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

Texture::Texture(const char* filepath)
{
    SDL_Surface* data = IMG_Load(filepath);
    if(!data)
    {
        Logger::LogError("Texture file does not exist.");
        return;
    }   

    this->pixels = new byte[data->h * data->pitch];
    byte* pixels = (byte*)data->pixels;
    
    for(int y = 0; y < data->h; y++)
        for(int x = 0; x < data->pitch; x++)
            this->pixels[(y * data->pitch) + x] = pixels[(y * data->pitch) + x];

    this->width = data->w;
    this->height = data->h;

    this->bytesPerPixel = data->format->BytesPerPixel; 

    TextureUtils::FlipTextureX(this);

    GLCALL(glGenTextures(1, &this->ID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->ID));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, this->bytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, this->pixels));

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    SDL_FreeSurface(data);
}
Texture::~Texture()
{
    GLCALL(glDeleteTextures(1, &this->ID));
}

uint32 Texture::GetID()
{
    return this->ID;
}
byte* Texture::GetPixels()
{
    return this->pixels;
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
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->ID));
}
void Texture::UnBind() const
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}