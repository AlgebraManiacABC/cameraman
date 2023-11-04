#include "assets.h"
#include "debug.h"
#include "textures.h"

GLuint textureList[NUM_TEXTURES] = {0};

char * assetPaths[NUM_TEXTURES]=
{
	"../assets/mainMenuBG.png",
	"../assets/levelSelectBG.png",
	"../assets/levelSprintBG.png"
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