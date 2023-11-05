#include <GL/glew.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define NUM_TEXTURES 6
#define TEX_ID_MAIN_MENU_BG     (0)
#define TEX_ID_LEVEL_SELECT_BG  (1)
#define TEX_ID_LEVEL_SPRINT_BG  (2)
#define TEX_ID_CAMERAMAN_R1     (3)
#define TEX_ID_BUTTON_PLAY      (4)
#define TEX_ID_BUTTON_QUIT_MAIN (5)
extern GLuint textureList[NUM_TEXTURES];

int loadAssets(void);

#ifdef __cplusplus
}
#endif