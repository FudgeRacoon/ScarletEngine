#include "scarlet/utils/SpriteUtils.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/system/AssetManager.hpp"
using namespace scarlet;

void SpriteUtils::FlipSpriteX(Sprite* sprite)
{
    std::vector<Vector2> newUv(4);
    std::vector<Vector2> oldUv = sprite->GetUV();
    
    newUv[0] = oldUv[2];
    newUv[1] = oldUv[3];
    newUv[2] = oldUv[0];
    newUv[3] = oldUv[1];

    sprite->SetUV(newUv);
}
void SpriteUtils::FlipSpriteY(Sprite* sprite)
{
    std::vector<Vector2> newUv(4);
    std::vector<Vector2> oldUv = sprite->GetUV();

    newUv[0] = oldUv[1];
    newUv[1] = oldUv[0];
    newUv[2] = oldUv[3];
    newUv[3] = oldUv[2];

    sprite->SetUV(newUv);
}

std::vector<Sprite*> SpriteUtils::SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight)
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

            Sprite* newSprite = AssetManager::AddSprite(name, sprite->GetTexture(), uv);

            sprites[counter++] = newSprite;
        }

    return sprites;
}