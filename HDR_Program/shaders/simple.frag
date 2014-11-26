#version 330 core

uniform sampler2D colorMap;
uniform int formatImage;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

vec4 toneMapping(vec4 color)
{
    vec4 tm;

    tm.r = color.r/(1.0 + color.r);
    tm.r = pow(tm.r, 1/2.2);

    tm.g = color.g/(1.0 + color.g);
    tm.g = pow(tm.g, 1/2.2);

    tm.b = color.b/(1.0 + color.b);
    tm.b = pow(tm.b, 1/2.2);

    tm.a = 1.0;

    return tm;
}

void main()
{
    vec4 color;
    color = texture(colorMap, texcoord);

    if (formatImage == 0)
    {
        float l = sqrt(color.r);
        color = vec4(l, l, l, 1.0);
    }
    else if (formatImage == 1)
    {
        float r = sqrt(color.r);
        float g = sqrt(color.g);
        float b = sqrt(color.b);

        color = vec4(r, g, b, 1.0);
    }
    else if (formatImage == 2)
        color = toneMapping(color);

    out_color = color;
}
