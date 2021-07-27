#ifndef GRIDLINES_HPP
#define GRIDLINES_HPP

#include "scarlet/math/Math.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/DebugRenderer.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

namespace scarlet
{
    class GridLines
    {   
    private:
        Camera* camera;

    private:
        uint32 cellWidth;
        uint32 cellHeight;
        Color lineColor;

    public:
        GridLines(Camera* camera);

    public:
        void SetCellWidth(uint32 width);
        void SetCellHeight(uint32 height);
        void SetColor(Color color);

    public:
        void OnRender();
    };
}

#endif