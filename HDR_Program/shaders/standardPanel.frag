#version 130

uniform sampler2D imgTexFront;
uniform int tonemap;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

vec4 toneMapping(vec4 color)
{
    vec4 tm;

    float r = color.r;
    float g = color.g;
    float b = color.b;

    tm.r = r/(1.0 + r);
    tm.r = pow(tm.r, 1/2.2);

    tm.g = g/(1.0 + g);
    tm.g = pow(tm.g, 1/2.2);

    tm.b = b/(1.0 + b);
    tm.b = pow(tm.b, 1/2.2);

    tm.a = 1.0;

    return tm;
}

void main()
{
    vec4 color;
    color = texture(imgTexFront, texcoord);

//    if (tonemap == 1)
        color = toneMapping(color);

    out_color = color;
}

