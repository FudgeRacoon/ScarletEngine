#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <assert.h>

#include "scarlet/utils/OpenGLDebug.hpp"

#ifdef SCARLET_NODEBUG
    #define SCARLET_CORE_ASSERT(_EXPR)
#else
    #define SCARLET_CORE_ASSERT(_EXPR)  assert(_EXPR)
    #define GLCALL(_EXPR) GLClearError();\
        _EXPR;\
        SCARLET_CORE_ASSERT(GLLogCall())    
#endif

#endif