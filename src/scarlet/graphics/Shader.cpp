#include "scarlet/graphics/Shader.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

const char* Shader::defaultVertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 fTexCoord;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_proj;\n"
"void main()\n"
"{\n"
"   vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   transformedVertex = transformedVertex * u_model;\n"
"   transformedVertex = transformedVertex * u_view;\n"
"   transformedVertex = transformedVertex * u_proj;\n"
"   gl_Position = transformedVertex;\n"
"   fTexCoord = aTexCoord;\n"
"}\0";

Shader::Shader(const char* fragmentShader)
{
    GLCALL(this->programID = glCreateProgram());

    if(this->programID == 0)
    {
        Logger::LogError("Failed to create shader program.");
        return;
    }

    CreateShaderWithSourceInternal(defaultVertexShaderSource, GL_VERTEX_SHADER);
    CreateShaderWithFileInternal(fragmentShader, GL_FRAGMENT_SHADER);

    GLCALL(glLinkProgram(this->programID));
    GLCALL(glValidateProgram(this->programID));

    int result;
    char buffer[512];
    GLCALL(glGetProgramiv(this->programID, GL_LINK_STATUS, &result));

    if(result == 0)
    {
        GLCALL(glGetProgramInfoLog(this->programID, 512, nullptr, buffer));
        Logger::LogError("Failed to link Shader\n%s", buffer);
        return;
    }
}
Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
    GLCALL(this->programID = glCreateProgram());

    if(this->programID == 0)
    {
        Logger::LogError("Failed to create shader program.");
        return;
    }

    CreateShaderWithFileInternal(vertexShader, GL_VERTEX_SHADER);
    CreateShaderWithFileInternal(fragmentShader, GL_FRAGMENT_SHADER);

    GLCALL(glLinkProgram(this->programID));
    GLCALL(glValidateProgram(this->programID));

    int result;
    char buffer[512];
    GLCALL(glGetProgramiv(this->programID, GL_LINK_STATUS, &result));

    if(result == 0)
    {
        GLCALL(glGetProgramInfoLog(this->programID, 512, nullptr, buffer));
        Logger::LogError("Failed to link Shader\n%s", buffer);
        return;
    }
}
Shader::~Shader()
{
    GLCALL(glDeleteProgram(this->programID));
}

void Shader::CreateShaderWithFileInternal(const char* filepath, int shaderType)
{
    std::string source = ParseShaderInternal(filepath);
    if(source.empty())
        return;

    const char* source_c_str = source.c_str();

    GLCALL(int shader = glCreateShader(shaderType));
    GLCALL(glShaderSource(shader, 1, &source_c_str, nullptr));
    GLCALL(glCompileShader(shader));

    int result;
    char buffer[512];
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));

    if(result == 0)
    {
        GLCALL(glGetShaderInfoLog(shader, 512, nullptr, buffer));
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: Logger::LogError("Failed to compile Vertex Shader.\n%s", buffer); return;
            case GL_FRAGMENT_SHADER: Logger::LogError("Failed to compile Fragment Shader.\n%s", buffer); return;
        }
    }

    GLCALL(glAttachShader(this->programID, shader));
    GLCALL(glDeleteShader(shader));
}
void Shader::CreateShaderWithSourceInternal(const char* source, int shaderType)
{
    GLCALL(int shader = glCreateShader(shaderType));
    GLCALL(glShaderSource(shader, 1, &source, nullptr));
    GLCALL(glCompileShader(shader));

    int result;
    char buffer[512];
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));

    if(result == 0)
    {
        GLCALL(glGetShaderInfoLog(shader, 512, nullptr, buffer));
        Logger::LogError("Failed to compile Vertex Shader.\n%s", buffer);
        return;
    }

    GLCALL(glAttachShader(this->programID, shader));
    GLCALL(glDeleteShader(shader));
}
std::string Shader::ParseShaderInternal(const char* filepath)
{
    std::fstream file(filepath, std::ios::in);

    if(!file)
    {
        Logger::LogError("Failed to open shader file.");
        return "";
    }

    std::string line;
    std::stringstream ss;

    while(getline(file, line))
        ss << line << '\n';
    
    return ss.str();
}

void Shader::SetBool(std::string varName, int value) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform1i(uniformID, value));
}
void Shader::SetInt(std::string varName, int value) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform1i(uniformID, value));
}
void Shader::SetFloat(std::string varName, float value) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform1f(uniformID, value));
}
void Shader::SetVec2i(std::string varName, Vector2 v) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform2i(uniformID, (int)v.x, (int)v.y));
}
void Shader::SetVec2f(std::string varName, Vector2 v) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform2f(uniformID, v.x, v.y));
}
void Shader::SetVec4i(std::string varName, Vector4 v) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform4i(uniformID, (int)v.x, (int)v.y, (int)v.z, (int)v.w));
}
void Shader::SetVec4f(std::string varName, Vector4 v) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniform4f(uniformID, v.x, v.y, v.z, v.w));
}
void Shader::SetMat4(std::string varName, Matrix4 m) const
{
    GLCALL(int uniformID = glGetUniformLocation(this->programID, varName.c_str()));
    GLCALL(glUniformMatrix4fv(uniformID, 1, false, m.GetValuePointer()));
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(this->programID));
}
void Shader::UnBind() const
{
    GLCALL(glUseProgram(0));
}