#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;

out vec3 ourColor;
out vec2 textCoords;

uniform mat4 transformMatrix;

void main()
{
  gl_Position = transformMatrix * vec4(position, 1.0f);
  ourColor = color;
  textCoords = vec2(textureCoords.x, 1.0 - textureCoords.y);
}