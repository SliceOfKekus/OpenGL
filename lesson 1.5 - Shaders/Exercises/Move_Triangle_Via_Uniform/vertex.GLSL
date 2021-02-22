#version 330 core
layout (location = 0) in vec3 position;

uniform float offSetX;
uniform float offSetY;
void main()
{
  gl_Position = vec4(position.x + offSetX, position.y + offSetY, position.z, 1.0f);
}