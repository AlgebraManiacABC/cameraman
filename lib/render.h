#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#ifdef __cplusplus
extern "C"
{
#endif

void initRenderer(void);

void renderBackground(GLuint texture);

#ifdef __cplusplus
}
#endif