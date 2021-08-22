#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "GL/glew.h"

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
        FrameBufferSpecification spec;

    public:
        FrameBuffer();
        ~FrameBuffer();
    
    public:
        uint32 GetFrameBufferID();
        uint32 GetColorAttachmentID();

    public:
        void AttachColorTexture(FrameBufferSpecification& spec);
        void AttachDepthTexture(FrameBufferSpecification& spec);
        
    public:
        void Resize(uint32 width, uint32 height);
        int ReadPixel(int32 format, int32 type, int x, int y);
    
    public:
        void Bind();
        void UnBind();
    };
}

#endif