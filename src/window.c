#include "window.h"
#include "debug.h"

//	What functions needed?
//
//	* Wrap:
//	 - SDL_Init
//	 - SDL_CreateWindow
//	 - SDL_GL_CreateContext
//	 - glewInit

int initWindow(Uint32 SDL_initFlags,
				Uint32 SDL_winFlags,
				const char * winTitle,
				Uint32 win_x, Uint32 win_y, Uint32 win_w, Uint32 win_h,
				SDL_Window ** w, SDL_GLContext * glContext)
{
	int err = EXIT_SUCCESS;
	if( (err = SDL_Init(SDL_initFlags)) )
	{
		setError(ERR_MESG,"SDL Initialization error: %s",SDL_GetError());
		return EXIT_FAILURE;
	}

	(*w) = SDL_CreateWindow(winTitle, win_x, win_y, win_w, win_h, SDL_winFlags);
	if(!(*w))
	{
		setError(ERR_MESG,"SDL Window creation failure: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	(*glContext) = SDL_GL_CreateContext(*w);
	if(!(*glContext))
	{
		setError(ERR_MESG,"SDL GL Context creation failure: %s",SDL_GetError());
		SDL_DestroyWindow((*w));
		SDL_Quit();
		return EXIT_FAILURE;
	}

	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		setError(ERR_MESG,"Glew initialization failure: %s",glewGetErrorString(glewError));
		SDL_GL_DeleteContext((*glContext));
		SDL_DestroyWindow((*w));
		SDL_Quit();
		return EXIT_FAILURE;
	}

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback,0);

	return EXIT_SUCCESS;
}