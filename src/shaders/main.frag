#version 330 core

out vec4 FragColor;
vec4 getTexture();

void main()
{
	vec4 texColor = getTexture();
	FragColor = texColor;
}