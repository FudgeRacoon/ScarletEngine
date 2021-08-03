#version 330 core

in vec4 fColor;
in vec2 fTexCoords;
in float fTexIndex;

out vec4 color;

uniform sampler2D textures[32];

void main()
{
    vec4 normalizedColor = vec4(fColor.x / 255.0, fColor.y / 255.0, fColor.z / 255.0, fColor.w / 255.0);

    int textureIndex = int(fTexIndex);
    vec4 texel = texture(textures[textureIndex], fTexCoords) * normalizedColor;

    if(texel.w < 0.1)
        discard;

    color = texel;
}