#include "scarlet/utils/TextureUtils.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/system/AssetPool.hpp"
using namespace scarlet;

void TextureUtils::FlipTextureX(Texture* texture)
{
    int width = texture->GetWidth();
    int height = texture->GetHeight();
    int bytesPerPixel = texture->GetBytesPerPixel();
    byte* pixels = texture->GetPixels();

    int pitch = width * bytesPerPixel;

    byte* topPixels = pixels;
    byte* bottomPixels = pixels + ((height - 1) * pitch);

    for(int y = 0; y < height / 2; y++)
    {
        byte* tempTopBuffer = new byte[pitch];
        byte* tempBottomBuffer = new byte[pitch];

        memcpy(tempTopBuffer, topPixels, pitch);
        memcpy(tempBottomBuffer, bottomPixels, pitch);

        memcpy(topPixels, tempBottomBuffer, pitch);
        memcpy(bottomPixels, tempTopBuffer, pitch);

        topPixels += pitch;
        bottomPixels -= pitch;

        delete[] tempTopBuffer;
        delete[] tempBottomBuffer;
    }
}
void TextureUtils::FlipTextureY(Texture* texture)
{
    
}

std::vector<Sprite*> TextureUtils::SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight)
{
    int counter = 0;

    float width = sprite->GetTexture()->GetWidth();
    float height = sprite->GetTexture()->GetHeight();

    int horzintalNumOfSprites = width / spriteWidth;
    int verticalNumOfSprites = height / spriteHeight;

    std::vector<Vector2> uv(4);
    std::vector<Sprite*> sprites(horzintalNumOfSprites * verticalNumOfSprites);

    for(int y = 1; y <= verticalNumOfSprites; y++)
        for(int x = 0; x < horzintalNumOfSprites; x++)
        {
            float currentWidth = spriteWidth * x;
            float currentHeight = spriteHeight * y;

            float xBottom = currentWidth / width;
            float yBottom = (height - currentHeight) / height;

            float xTop = (currentWidth + spriteWidth) / width;
            float yTop = ((height - currentHeight) + spriteHeight) / height;

            uv[0] = Vector2(xBottom, yBottom);
            uv[1] = Vector2(xTop, yBottom);
            uv[2] = Vector2(xTop, yTop);
            uv[3] = Vector2(xBottom, yTop);

            std::string name = sprite->GetName();
            name.append("_" + std::to_string(counter));

            Sprite* newSprite = AssetPool::AddSprite(name, sprite->GetTexture(), uv);

            sprites[counter++] = newSprite;
        }

    return sprites;
}