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
    enum Graphics_BlendFunction
    {
        SCARLET_SRC_ALPHA = 0x0302,
        SCARLET_ONE_MINUS_SRC_ALPHA = 0x0303
    };

    enum Graphics_BufferType
    {
        SCARLET_BUFFER_DEPTH   = 0x00000100,
        SCARLET_BUFFER_STENCIL = 0x00000400,
        SCARLET_BUFFER_COLOR   = 0x00004000
    };

    enum Graphics_DrawMode
    {
        SCARLET_LINES                    = 0x0001, 
        SCARLET_LINE_LOOP                = 0x0002, 
        SCARLET_LINE_STRIP               = 0x0003, 
        SCARLET_TRIANGLES                = 0x0004, 
        SCARLET_TRIANGLE_STRIP           = 0x0005, 
        SCARLET_TRIANGLE_FAN             = 0x0006, 
        SCARLET_LINES_ADJACENCY          = 0x000A, 
        SCARLET_LINE_STRIP_ADJACENCY     = 0x000B, 
        SCARLET_TRIANGLES_ADJACENCY      = 0x000C,
        SCARLET_TRIANGLE_STRIP_ADJACENCY = 0x000D
    };

    class GraphicsContext
    {
    private:
        static Vector4 viewport;

    public:
        static void OnInit();

    public:
        static Vector4 GetViewPort();
        static uint32 GetMaxTextureSlots();

    public:
        static void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetBlendingFunction(Graphics_BlendFunction sFactor, Graphics_BlendFunction dFactor);
        static void SetClearColor(Color color);

    public:
        static void EnableBlending(bool enable);

    public:
        static void ClearBuffers(Graphics_BufferType buffers);
        static void SwapBuffers();
    
    public:
        static void DrawArrays(Graphics_DrawMode mode, VertexArray* vao, uint32 count);
        static void DrawElements(Graphics_DrawMode mode, VertexArray* vao, IndexBuffer* ibo, uint32 count);
    };
}

#endif