#include <GL/glew.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define NUM_TEXTURES 3
extern GLuint textureList[NUM_TEXTURES];
#define TEX_ID_MAIN_MENU_BG    (0)
#define TEX_ID_LEVEL_SELECT_BG (1)
#define TEX_ID_LEVEL_SPRINT_BG (2)

int loadAssets(void);

#ifdef __cplusplus
}
#endif