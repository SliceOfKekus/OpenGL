#version 330 core
in vec3 ourColor;
in vec2 textCoords;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixCoeff;

void main()
{
  color = mix(texture(ourTexture1, textCoords), 
			  texture(ourTexture2, vec2(textCoords.x, 1 - textCoords.y)), mixCoeff);
}