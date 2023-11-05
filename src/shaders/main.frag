#version 330 core

out vec4 FragColor;
vec4 getTexture();
uniform float u_alphaTest = 0.01;

void main()
{
	vec4 texColor = getTexture();
	if (texColor.a < u_alphaTest) {
		discard;  // don't draw this pixel
	}
	FragColor = texColor;
}