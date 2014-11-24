#version 330

uniform sampler2D imageTex;

in vec2 texcoord;

out vec4 outputColor;

void main()
{
//   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 img = texture(imageTex, texcoord);

//    img.r = (img.r == 0)? 1.0 : 0.0;

    img.a = 1.0;

    outputColor = img;
}
