#version 330 core

layout(location = 0) in vec3  aPos;
layout(location = 1) in vec4  aColor;
layout(location = 2) in vec2  aTexCoords;
layout(location = 3) in float aTexIndex;
layout(location = 4) in float aInstanceID;

out vec4  fColor;
out vec2  fTexCoords;
out float fTexIndex;
out float fInstanceID;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    fColor = aColor;
    fTexCoords = aTexCoords;
    fTexIndex = aTexIndex;
    fInstanceID = aInstanceID;

    vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    transformedVertex = transformedVertex * uView;
    transformedVertex = transformedVertex * uProj;

    gl_Position = transformedVertex;
}
