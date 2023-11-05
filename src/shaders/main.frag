#version 330 core

out vec4 FragColor;
vec4 getTexture();

void main()
{
	vec4 texColor = getTexture();
	if (texColor.a == 0) {
		discard;
	}
	FragColor = texColor;
}