#version 130

uniform sampler2D imgTexFront;
uniform float parameters[7];
uniform int tonemap;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

float processTM(float val, float l, int channel)
{
    float c = 0.5;
    float a = 0.5;

    float ILocal = c*val + (1.f - c)*l;
    float IGlobal = c*parameters[channel] + (1.f - c)*parameters[4];
    float Ia = a*ILocal + (1.f - a)*IGlobal;
    val /= val + pow(parameters[5] * Ia, parameters[6]);

    return val;
}

vec4 toneMapping(vec4 color)
{
    vec4 tm;

    float l = 0.2125*color.r + 0.7154*color.g + 0.0721*color.b;
    l *= 100.0;

    tm.r = processTM(100.0*color.r, l, 0);
    tm.g = processTM(100.0*color.g, l, 1);
    tm.b = processTM(100.0*color.b, l, 2);

    tm.a = 1.0;

    return tm;
}

void main()
{
    vec4 color;
    color = texture(imgTexFront, texcoord);

    if (tonemap == 1)
        color = toneMapping(color);

    out_color = color;
}

