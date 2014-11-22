#version 330 core

uniform sampler2D colorMap;
uniform sampler2D sampler;

in vec4 position_obj;
in vec4 position_view;

in vec2 texcoord;

out vec4 out_color;

void main()
{
    //out_color = vec4(position_obj.xyz*.5 + vec3(.5), 1.);
    //out_color = vec4(texcoord.xy, 0.0, 1.);
    out_color = texture(colorMap, texcoord);
}
