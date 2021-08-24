#ifndef GRAPHICSCONTEXT_HPP
#define GRAPHICSCONTEXT_HPP

#include "GL/glew.h"

#include "scarlet/core/Window.hpp"
#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"
#include "scarlet/core/math/Color.hpp"
#include "scarlet/core/math/Vector4.hpp"

#include "scarlet/graphics/buffer/FrameBuffer.hpp"
#include "scarlet/graphics/buffer/IndexBuffer.hpp"
#include "scarlet/graphics/VertexArray.hpp"

namespace scarlet
{   
    enum GraphicsBlendFunction
    {
        SCARLET_ZERO                     = 0, 
        SCARLET_ONE                      = 1, 
        SCARLET_SRC_COLOR                = 0x0300, 
        SCARLET_ONE_MINUS_SRC_COLOR      = 0x0301,  
        SCARLET_SRC_ALPHA                = 0x0302,
        SCARLET_ONE_MINUS_SRC_ALPHA      = 0x0303,
        SCARLET_DST_ALPHA                = 0x0304,
        SCARLET_ONE_MINUS_DST_ALPHA      = 0x0305, 
        SCARLET_DST_COLOR                = 0x0306, 
        SCARLET_ONE_MINUS_DST_COLOR      = 0x0307, 
        SCARLET_CONSTANT_COLOR           = 0x8001, 
        SCARLET_ONE_MINUS_CONSTANT_COLOR = 0x8002, 
        SCARLET_CONSTANT_ALPHA           = 0x8003, 
        SCARLET_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
        SCARLET_SRC_ALPHA_SATURATE       = 0x0308,
    };

    enum GraphicsBufferType
    {
        SCARLET_BUFFER_DEPTH   = 0x00000100,
        SCARLET_BUFFER_STENCIL = 0x00000400,
        SCARLET_BUFFER_COLOR   = 0x00004000
    };

    enum GraphicsDrawMode
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
        static FrameBuffer* renderTarget;

    public:
        static void OnInit();

    public:
        static Vector4 GetViewPort();
        static FrameBuffer* GetRenderTarget();
        static uint32 GetMaxTextureSlots();
        static const byte* GetGlVersion();

    public:
        static void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetBlendingFunction(GraphicsBlendFunction sFactor, GraphicsBlendFunction dFactor);
        static void SetClearColor(Color color);

    public:
        static void EnableBlending(bool enable);

    public:
        static void ClearBuffers(GraphicsBufferType buffers);
        static void SwapBuffers();
    };
}

#endif