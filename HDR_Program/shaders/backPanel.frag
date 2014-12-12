#version 130

uniform sampler2D imgTexBack;
uniform sampler2D corTex;
uniform int tonemap;

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
    color = texture(imgTexBack, texcoord);

    float l = 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
    l = clamp(sqrt(l), 0.0, 254.0/255.0);
    color = texture(corTex, vec2(l, 1.0));

    if (tonemap == 1)
        color = vec4(1.0, 1.0, 1.0, 1.0);

    out_color = color;
}
