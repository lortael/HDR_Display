#version 330 core

uniform sampler2D colorMap;
uniform int formatImage;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

void main()
{
    //out_color = vec4(position_obj.xyz*.5 + vec3(.5), 1.);
    //out_color = vec4(texcoord.xy, 0.0, 1.);
    vec4 color;
//    color = (formatImage == 0)? color.rrra : color;

    color = texture(colorMap, texcoord);
//    if (formatImage == 0)
//        color = texture(colorMap, texcoord).rrra;
//    else
//        color = texture(colorMap, texcoord);

//    color.g = (color.g == 0)? 1 : 0;

    out_color = color;
}
