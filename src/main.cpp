#include "main.h"
#include "debug.h"
#include "window.h"
#include "game.h"

#define INITIAL_WINDOW_W 800
#define INITIAL_WINDOW_H 640

int ww = INITIAL_WINDOW_W;
int wh = INITIAL_WINDOW_H;

SDL_Window *w = NULL;

int main(int argc, char * argv[])
{
	SDL_GLContext glContext;
	Uint32 err;
	err = initWindow(SDL_INIT_EVERYTHING, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL,
				"The Cameraman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				INITIAL_WINDOW_W, INITIAL_WINDOW_H, &w, &glContext);
	if(err)
	{
		fprintf(stderr,"Error during intialization: %s\n",getError());
		return EXIT_FAILURE;
	}

	playGame();

	SDL_DestroyWindow(w);
	SDL_GL_DeleteContext(glContext);
	SDL_Quit();
	return EXIT_SUCCESS;
}