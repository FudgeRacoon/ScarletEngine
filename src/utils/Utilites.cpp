#include "core/utils/Utilites.hpp"
#include "core/renderer/Texture.hpp"
#include "core/Sprite.hpp"
#include "core/manager/AssetPool.hpp"
using namespace scarlet;

void Utilites::FlipTextureX(Texture* texture)
{
    int width = texture->GetWidth();
    int height = texture->GetHeight();
    int bytesPerPixel = texture->GetBytesPerPixel();
    uint8* pixels = texture->GetPixels();

    int pitch = width * bytesPerPixel;

    uint8* topPixels = pixels;
    uint8* bottomPixels = pixels + ((height - 1) * pitch);

    for(int y = 0; y < height / 2; y++)
    {
        uint8* tempTopBuffer = new uint8[pitch];
        uint8* tempBottomBuffer = new uint8[pitch];

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
void Utilites::FlipTextureY(Texture* texture)
{
    
}

std::vector<Sprite*> Utilites::SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight)
{
    int counter = 0;

    float width = sprite->GetTexture()->GetWidth();
    float height = sprite->GetTexture()->GetHeight();

    int horzintalNumOfSprites = width / spriteWidth;
    int verticalNumOfSprites = height / spriteHeight;

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

            Vector2 v1(xBottom, yBottom);
            Vector2 v2(xTop, yBottom);
            Vector2 v3(xTop, yTop);
            Vector2 v4(xBottom, yTop);

            std::string name = sprite->GetName();
            name.append("_" + std::to_string(counter));

            Sprite* newSprite = AssetPool::AddSprite(name, sprite->GetTexture());
            newSprite->GetRect()->SetUV(v1, v2, v3, v4);

            sprites[counter++] = newSprite;
        }

    return sprites;
}