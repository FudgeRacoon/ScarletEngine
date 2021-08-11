#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <stdio.h>

#include "scarlet/debug/OpenGLDebug.hpp"

#ifdef SCARLET_NODEBUG
    #define SCARLET_CORE_ASSERT(_EXPR, ...)
#else
    #define SCARLET_CORE_ASSERT(_EXPR, ...)\
        if(!(_EXPR))\
        {\
            printf("Assertion Failed: %s | File %s | Line %d\n", #_EXPR, __FILE__, __LINE__);\
            printf("Assertion Message: %s\n", ##__VA_ARGS__);\
            exit(EXIT_FAILURE);\
        }\

    #define GLCALL(_EXPR) GLClearError();\
        _EXPR;\
        SCARLET_CORE_ASSERT(GLLogCall())    
#endif

#endif