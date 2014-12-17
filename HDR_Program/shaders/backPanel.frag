#version 130

uniform sampler2D imgTexBack;
uniform sampler2D corTex;
uniform int tonemap;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

void main()
{
    vec4 color;
    color = texture(imgTexBack, texcoord);    

    if (tonemap == 2)
        color = vec4(1.0, 1.0, 1.0, 1.0);
    else
    {
        float l = 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
        l = clamp(l, 0.0, 1.0);
        color = texture(corTex, vec2(l, 1.0));
    }

    out_color = vec4(color.r, color.g, color.b, 1.0);
}

