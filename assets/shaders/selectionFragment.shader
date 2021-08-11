#version 330 core

in vec2 fTexCoords;
in float fTexIndex;
in float fInstanceID;

out vec4 color;

uniform sampler2D textures[32];

void main()
{
    if(fTexIndex > 0)
    {
        int textureIndex = int(fTexIndex);
        vec4 texel = texture(textures[textureIndex], fTexCoords);

        if(texel.w < 0.1)
            discard;
    }

    color = vec4(fInstanceID, fInstanceID, fInstanceID, 1.0);
}