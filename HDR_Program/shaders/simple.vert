#version 330

in vec4 vtx_position;

in vec2 vtx_texcoord;
out vec2 texcoord;

void main()
{
    texcoord = vtx_texcoord;
    gl_Position = vtx_position;
}
