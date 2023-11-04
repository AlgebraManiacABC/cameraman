#include "assets.h"
#include "debug.h"
#include "textures.h"

GLuint textureMainMenuBG = 0;
GLuint textureLevelSelectBG = 0;

int loadAssets(void)
{
	stbi_set_flip_vertically_on_load(true);
	if(! ((textureMainMenuBG = textureFromFile("../assets/mainMenu.png") )) )
	{
		setError(ERR_MESG,"Couldn't load \"%s\": %s","../assets/mainMenu.png",getError());
		return EXIT_FAILURE;
	}
	if(! ((textureLevelSelectBG = textureFromFile("../assets/levelSelect.png") )) )
	{
		setError(ERR_MESG,"Couldn't load \"%s\": %s","..assets/levelSelect.png",getError());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}