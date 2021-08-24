#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"

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
        uint32 frameBufferId;
        uint32 colorAttachmentId;
        uint32 depthAttachmentId;
        FrameBufferSpecification spec;

    public:
        FrameBuffer();
        ~FrameBuffer();
    
    public:
        uint32 GetFrameBufferId();
        uint32 GetColorAttachmentId();
        uint32 GetDepthAttachmentId();

    public:
        void Resize(uint32 width, uint32 height);

    public:
        void AttachColorTexture(FrameBufferSpecification& spec);
        void AttachDepthTexture(FrameBufferSpecification& spec);
        
    public:
        int ReadPixel(uint32 format, uint32 type, int x, int y);
    
    public:
        void Bind();
        void UnBind();
    };
}

#endif