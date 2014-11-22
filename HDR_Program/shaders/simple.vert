#version 330 core

in vec3 vtx_position;

uniform mat4 mTransformation;

void main()
{
  //Version initiale du TD
  gl_Position = mTransformation * vec4(vtx_position.xyz, 1.);

  //TODO
}
