#version 330 core
out vec4 vertPos;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

//uniform mat4 transform;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    vertPos = gl_Position;
    texCoord = aTexCoord;
}