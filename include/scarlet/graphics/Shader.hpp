#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/math/Matrix4.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class AssetPool;

    class Shader
    {
    private:
        uint32_t programID;

    private:
        Shader(const char* vertexShader, const char* fragmentShader);
        ~Shader();

    private:
        void CreateShaderInternal(const char* filepath, int shaderType);
        std::string ParseShaderInternal(const char* filepath);

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
    
    friend AssetPool;
    };
}

#endif