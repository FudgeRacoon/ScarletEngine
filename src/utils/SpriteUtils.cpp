#include "core/utils/SpriteUtils.hpp"
using namespace scarlet;

std::vector<Sprite*>& SpriteUtils::SliceSprite(std::string name, Sprite* sprite, int spriteWidth, int spriteHeight, int numberOfSprites)
{
    float width = sprite->GetTexture()->GetWidth();
    float height = sprite->GetTexture()->GetHeight();

    int horzintalNumOfSprites = width / spriteWidth;
    int verticalNumOfSprites = height / spriteHeight;

    std::vector<Sprite*> sprites(numberOfSprites);

    for(int y = 0; y < verticalNumOfSprites; y++)
        for(int x = 0; x < horzintalNumOfSprites; x++)
        {
            float currentWidth = spriteWidth * x;
            float currentHeight = spriteHeight * (y + 1);

            float xBottom = currentWidth / width;
            float yBottom = (height - currentHeight) / height;

            float xTop = (currentWidth + spriteWidth) / width;
            float yTop = ((height - currentHeight) + spriteHeight) / height;

            Vector2 v1(xBottom, yBottom);
            Vector2 v2(xTop, yBottom);
            Vector2 v3(xTop, yTop);
            Vector2 v4(xBottom, yTop);
            
            Sprite* newSprite = AssetPool::AddSprite(name, sprite->GetTexture());
            newSprite->GetRect()->SetUV(v1, v2, v3, v4);
            sprites.push_back(newSprite);
        }

    return sprites;
}