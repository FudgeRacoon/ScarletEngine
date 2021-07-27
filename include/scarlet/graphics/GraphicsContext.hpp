#ifndef GRAPHICSCONTEXT_HPP
#define GRAPHICSCONTEXT_HPP

#include "GL/glew.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/core/Window.hpp"

#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector4.hpp"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{   
    enum BlendFunc
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

    class GraphicsContext
    {
    private:
        static Vector4 viewport;

    public:
        static void Init();

    public:
        static Vector4 GetViewPort();

    public:
        static void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetBlendingFunction(uint32 sFactor, uint32 dFactor);
        static void SetClearColor(Color color);

    public:
        static void EnableBlending(bool enable);

    public:
        static void ClearBuffers(uint32 buffers);
        static void SwapBuffers();
    };
}

#endif