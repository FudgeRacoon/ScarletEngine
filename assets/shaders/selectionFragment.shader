#version 330 core

in vec4  fColor;
in vec2  fTexCoords;
in float fTexIndex;
in float fInstanceID;

out int color;

uniform sampler2D textures[32];

void main()
{
    if(fTexIndex > 0)
    {
        vec4 texel = texture(textures[int(fTexIndex)], fTexCoords);

        if(texel.w < 0.1)
            discard;
    }

    color = int(fInstanceID);
}