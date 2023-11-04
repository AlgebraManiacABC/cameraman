#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "windows_compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
typedef uint32_t Uint32;

#define ERR_UNDEF (0)
#define ERR_NOFIL (1)
#define ERR_SHADE (2)
#define ERR_NULLP (3)
#define ERR_NOMEM (4)

typedef bool errType;
#define ERR_CODE (false)
#define ERR_MESG (true)

extern const char * errorMessages[];
extern const char * variableError;
extern char * editableError;
extern Uint32 lastErrorCode;

/**
 * Sets the error message to either a predefined error string (`ERR_CODE`) or a custom,
 * printf-style formatted string (`ERR_MESG`). The next argument is either the error code
 * or the formatted string (which would then be followed by any necessary matching variables)
 * 
 * @param type 
 * @param ... 
 */
void setError(errType type, ...);

/**
 * Gets the most current error string set by setError().
 * Please use as soon as an error is detected,
 * otherwise the error message may get stale.
 * 
 * @returns the error string as a const char *
 */
const char * getError(void);

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam );

#ifdef __cplusplus
}
#endif

#endif