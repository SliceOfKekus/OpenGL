#version 330 core

in vec3 posInColor;
out vec4 color;

void main()
{
  color = vec4(posInColor, 1.0f);
}