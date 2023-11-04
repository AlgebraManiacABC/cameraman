#include "game.h"
#include "shaders.h"
#include "debug.h"
#include "events.h"

void gameLoop(SDL_Window *w)
{
	int ww, wh;
	SDL_GetWindowSize(w,&ww,&wh);

	if(!loadUniversalShaders()) return;
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
}