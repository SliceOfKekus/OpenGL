#version 330 core
in vec2 textCoords;

out vec4 color;

uniform float mixValue;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
  color = mix(texture(ourTexture1, textCoords), texture(ourTexture2, textCoords), mixValue);
}