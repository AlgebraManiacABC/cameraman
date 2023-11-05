#include "assets.h"
#include "debug.h"
#include "textures.h"

GLuint textureList[NUM_TEXTURES] = {0};

char * assetPaths[NUM_TEXTURES]=
{
	"../assets/mainMenu.png",
	"../assets/levelSelectBG.png",
	"../assets/levelSprintBG.png",
	"../assets/levelSprintThumb.png",
	"../assets/pause.png",
	"../assets/cameraman_R1.png",
	"../assets/camera.png",
	"../assets/play.png",
	"../assets/quitMain.png",
	"../assets/resume.png",
	"../assets/levels.png",
	"../assets/floor.png",
	"../assets/vault.png",
	"../assets/player/Body1.png",
	"../assets/player/Body2.png",
	"../assets/player/Body3.png",
	"../assets/player/Body4.png",
	"../assets/sprinter/Sprinter1.png",
	"../assets/sprinter/Sprinter2.png",
	"../assets/sprinter/Sprinter3.png",
	"../assets/sprinter/Sprinter4.png",
	"../assets/ratingsBackground.png",
	"../assets/ratingsBar.png"
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