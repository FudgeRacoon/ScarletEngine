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
        int32 type;
        int32 format;
        int32 internalFormat;
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
    
    private:
        bool CheckStatus();

    public:
        uint32 GetFrameBufferID();
        uint32 GetColorAttachmentID();

    public:
        int ReadPixel(int32 format, int32 type, int x, int y);
        void AttachColorTexture(FrameBufferSpecification& spec);
        
    public:
        void Bind();
        void UnBind();
    };
}

#endif