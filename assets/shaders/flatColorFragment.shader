#version 330 core

in vec4 fColor;

out vec4 color;

void main()
{
    vec4 normalizedColor = vec4(fColor.x / 255.0, fColor.y / 255.0, fColor.z / 255.0, fColor.w / 255.0);
    color = normalizedColor;
}