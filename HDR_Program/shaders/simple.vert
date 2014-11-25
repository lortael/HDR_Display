#version 330 core

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform mat4 mTransformation;

in vec4 vtx_position;
in vec2 vtx_texcoord;

out vec4 position_obj;
out vec4 position_view;
out vec2 texcoord;

void main() {
    position_obj = vtx_position;
    position_view = view_matrix * position_obj;

    texcoord = vtx_texcoord;

    gl_Position = projection_matrix * position_view;
}
