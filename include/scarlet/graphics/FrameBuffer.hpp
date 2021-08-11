#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "scarlet/graphics/GraphicsContext.hpp"

#include "scarlet/common/Types.hpp"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{   
    struct FrameBufferSpecification
    {
        uint32 width;
        uint32 height;
        Graphics_Type type;
        Graphics_Format format;
        Graphics_Format internalFormat;
    };

    class FrameBuffer
    {
    private:
        uint32 frameBufferID;
        uint32 colorAttachmentID;

    private:
        uint32 width;
        uint32 height;

    public:
        FrameBuffer();
        ~FrameBuffer();

    public:
        uint32 GetFrameBufferID();
        uint32 GetColorAttachmentID();

    public:
        bool CheckStatus();

    public:
        void AttachColorTexture(FrameBufferSpecification& spec);

    public:
        int ReadPixel(Graphics_Format format, Graphics_Type type, int x, int y, uint32 colorAttachmentIndex = 0);

    public:
        void Bind();
        void UnBind();
    };
}

#endif