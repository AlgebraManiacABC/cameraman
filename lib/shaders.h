#ifndef SHADERS_H
#define SHADERS_H

#ifdef __cplusplus
extern "C"
{
#endif

#define GLEW_STATIC
#include <stdio.h>
#include <GL/glew.h>
#include <stdarg.h>

GLuint createShader(const char * shaderFilename, GLenum shaderType);

GLuint createProgram(size_t shaderCount, ...);

#ifdef __cplusplus
}
#endif

#endif