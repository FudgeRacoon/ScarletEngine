#include "scarletEditor/GridLines.hpp"
using namespace scarlet;

GridLines::GridLines(Camera* camera)
{
    this->camera = camera;

    this->cellWidth = 32;
    this->cellHeight = 32;
    this->lineColor = Color(44, 44, 44);
}

void GridLines::SetCellWidth(uint32 width)
{
    this->cellWidth = width;
}
void GridLines::SetCellHeight(uint32 height)
{
    this->cellHeight = height;
}
void GridLines::SetColor(Color color)
{
    this->lineColor = color;
}

void GridLines::OnRender()
{   
    float worldWidth = camera->GetRightPlane() * 2;
    float worldHeight = camera->GetTopPlane() * 2;

    int32 cellHorizontalCount = (worldWidth / this->cellWidth);
    int32 cellVerticalCount = (worldHeight / this->cellHeight);

    float cameraOffsetX = camera->position.x - (worldWidth / 2);
    float cameraOffsetY = camera->position.y + (worldHeight / 2);

    int32 startX = ((int32)(cameraOffsetX / this->cellWidth) - 1) * this->cellWidth;
    int32 startY = ((int32)(cameraOffsetY / this->cellHeight) + 1) * this->cellHeight;

    int32 maxCount = Math::Max(cellHorizontalCount, cellVerticalCount);

    Renderer::BeginScene(this->camera);

    for(int32 i = 0; i < maxCount + 10; i++)
    {
        int32 x = startX + (this->cellWidth * i);
        int32 y = startY - (this->cellHeight * i);

        Renderer::DrawLine(startX, y, (startX + worldWidth) * 2, y, this->lineColor);
        Renderer::DrawLine(x, startY, x, (startY - worldHeight) * 2, this->lineColor);
    }

    Renderer::EndScene();
}