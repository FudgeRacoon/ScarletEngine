#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"

#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"
#include "scarlet/core/math/Matrix4.hpp"

namespace scarlet
{
    class AssetManager;

    class Shader
    {
    private:
        uint32_t programId;

    private:
        Shader(const char* vertexShader, const char* fragmentShader);
        ~Shader();

    private:
        std::string ParseShader(const char* filepath);
        void CreateShader(const char* filepath, int shaderType);

    public:
        void SetBool(std::string varName, int value) const;
        void SetInt(std::string varName, int value) const;
        void SetFloat(std::string varName, float value) const;
        void SetVec2i(std::string varName, Vector2 v) const;
        void SetVec2f(std::string varName, Vector2 v) const;
        void SetVec4i(std::string varName, Vector4 v) const;
        void SetVec4f(std::string varName, Vector4 v) const;
        void SetMat4(std::string varName, Matrix4 m) const;

    public:
        void Bind() const;
        void UnBind() const;
    
    friend AssetManager;
    };
}

#endif