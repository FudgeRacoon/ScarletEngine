#ifndef GRAPHICSCONTEXT_HPP
#define GRAPHICSCONTEXT_HPP

#include "GL/glew.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/core/Window.hpp"

#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"

#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector4.hpp"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{   
    enum BlendFunction
    {
        SCARLET_SRC_ALPHA = 0x0302,
        SCARLET_ONE_MINUS_SRC_ALPHA = 0x0303,
    };

    enum BufferType
    {
        SCARLET_BUFFER_DEPTH = 0x00000100,
        SCARLET_BUFFER_STENCIL = 0x00000400,
        SCARLET_BUFFER_COLOR = 0x00004000
    };

    enum DrawMode
    {
        SCARLET_POINTS = 0x0000,
        SCARLET_LINES = 0x0001,
        SCARLET_LINE_LOOP = 0x0002,
        SCARLET_TRIANGLES = 0x0004
    };

    class GraphicsContext
    {
    private:
        static Vector4 viewport;

    public:
        static void Init();

    public:
        static Vector4 GetViewPort();
        static uint32 GetMaxTextureSlots();

    public:
        static void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetBlendingFunction(BlendFunction sFactor, BlendFunction dFactor);
        static void SetClearColor(Color color);

    public:
        static void EnableBlending(bool enable);

    public:
        static void ClearBuffers(uint32 buffers);
        static void SwapBuffers();
    
    public:
        static void DrawArrays(DrawMode mode, VertexArray* vao, uint32 count);
        static void DrawElements(DrawMode mode, VertexArray* vao, IndexBuffer* ibo, uint32 count);
    };
}

#endif