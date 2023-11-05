#include "assets.h"
#include "debug.h"
#include "textures.h"

GLuint textureList[NUM_TEXTURES] = {0};

char * assetPaths[NUM_TEXTURES]=
{
	"../assets/mainMenuBG.png",
	"../assets/levelSelectBG.png",
	"../assets/levelSprintBG.png",
	"../assets/levelSprintThumb.png",
	"../assets/cameraman_R1.png",
	"../assets/play.png",
	"../assets/quitMain.png",
	"../assets/floor.png"
};

GLuint TEX_ID_LEVEL_THUMBS[LEVEL_COUNT] =
{
	TEX_ID_LEVEL_SPRINT_THUMB
};

int loadAssets(void)
{
	stbi_set_flip_vertically_on_load(true);
	for(int i=0; i<NUM_TEXTURES; i++)
	{
		textureList[i] = textureFromFile(assetPaths[i]);
		if(!textureList[i])
		{
			setError(ERR_MESG,"Couldn't load \"%s\": %s",assetPaths[i],getError());
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}