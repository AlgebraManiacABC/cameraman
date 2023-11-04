#include "game.h"
#include "shaders.h"
#include "debug.h"
#include "events.h"
#include "assets.h"
#include "render.h"

GLuint (*fnPointers[])(SDL_Window*) =
{
	NULL,
	mainMenu,
	levelSelect,
	levelSprint
};

void playGame(SDL_Window *w)
{
	int ww, wh;
	SDL_GetWindowSize(w,&ww,&wh);

	initRenderer();
	if(!loadUniversalShaders()) return;
	if(loadAssets()) return;

	GLuint status = STATUS_MAIN_MENU;
	while(status != STATUS_GAME_EXIT)
	{
		status = fnPointers[status](w);
		//switch(status)
		//{
		//	case STATUS_MAIN_MENU:
		//		status = mainMenu(w);
		//		break;
		//	case STATUS_LEVEL_SELECT:
		//		status = levelSelect(w);
		//		break;
		//	case STATUS_GAME_EXIT:
		//	default:
		//		return;
		//}
	}
}

GLuint mainMenu(SDL_Window *w)
{
	//fprintf(stderr,"Main Menu\n");
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SELECT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_MAIN_MENU_BG]);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSelect(SDL_Window *w)
{
	//fprintf(stderr,"Level Select\n");
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SPRINT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SELECT_BG]);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSprint(SDL_Window *w)
{
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SELECT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SPRINT_BG]);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}