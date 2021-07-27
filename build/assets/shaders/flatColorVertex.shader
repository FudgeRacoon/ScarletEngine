#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 fColor;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    transformedVertex = transformedVertex * uView;
    transformedVertex = transformedVertex * uProj;

    gl_Position = transformedVertex;

    fColor = aColor;
}