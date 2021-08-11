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
    enum Graphics_Format
    {
        SCARLET_STENCIL_INDEX   = 0x1901, 
        SCARLET_DEPTH_COMPONENT = 0x1902, 
        SCARLET_RED             = 0x1903, 
        SCARLET_GREEN           = 0x1904, 
        SCARLET_BLUE            = 0x1905, 
        SCARLET_RGB             = 0x1907, 
        SCARLET_RGBA            = 0x1908,
        SCARLET_BGR             = 0x80E0, 
        SCARLET_BGRA            = 0x80E1,
        SCARLET_DEPTH_STENCIL   = 0x84F9 
    };

    enum Graphics_Type
    {
        SCARLET_BYTE                           = 0x1400, 
        SCARLET_UNSIGNED_BYTE                  = 0x1401,
        SCARLET_SHORT                          = 0x1402, 
        SCARLET_UNSIGNED_SHORT                 = 0x1403, 
        SCARLET_INT                            = 0x1404, 
        SCARLET_UNSIGNED_INT                   = 0x1405, 
        SCARLET_FLOAT                          = 0x1406, 
        SCARLET_HALF_FLOAT                     = 0x140B, 
        SCARLET_UNSIGNED_BYTE_3_3_2            = 0x8032, 
        SCARLET_UNSIGNED_SHORT_4_4_4_4         = 0x8033, 
        SCARLET_UNSIGNED_SHORT_5_5_5_1         = 0x8034, 
        SCARLET_UNSIGNED_INT_8_8_8_8           = 0x8035, 
        SCARLET_UNSIGNED_INT_10_10_10_2        = 0x8036, 
        SCARLET_UNSIGNED_BYTE_2_3_3_REV        = 0x8362, 
        SCARLET_UNSIGNED_SHORT_5_6_5           = 0x8363, 
        SCARLET_UNSIGNED_SHORT_5_6_5_REV       = 0x8364, 
        SCARLET_UNSIGNED_SHORT_4_4_4_4_REV     = 0x8365, 
        SCARLET_UNSIGNED_SHORT_1_5_5_5_REV     = 0x8366, 
        SCARLET_UNSIGNED_INT_8_8_8_8_REV       = 0x8367, 
        SCARLET_UNSIGNED_INT_2_10_10_10_REV    = 0x8368, 
        SCARLET_UNSIGNED_INT_24_8              = 0x84FA, 
        SCARLET_UNSIGNED_INT_10F_11F_11F_REV   = 0x8C3B, 
        SCARLET_UNSIGNED_INT_5_9_9_9_REV       = 0x8C3E,
        SCARLET_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD
    };

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