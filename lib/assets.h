#include <GL/glew.h>
#include "game.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NUM_TEXTURES 22
#define TEX_ID_MAIN_MENU_BG       (0)
#define TEX_ID_LEVEL_SELECT_BG    (1)
#define TEX_ID_LEVEL_SPRINT_BG    (2)
#define TEX_ID_LEVEL_SPRINT_THUMB (3)
#define TEX_ID_PAUSE_MENU_BG      (4)
#define TEX_ID_CAMERAMAN_R1       (5)
#define TEX_ID_CAMERA             (6)
#define TEX_ID_BUTTON_PLAY        (7)
#define TEX_ID_BUTTON_QUIT_MAIN   (8)
#define TEX_ID_BUTTON_RESUME      (9)
#define TEX_ID_FLOOR              (10)
#define TEX_ID_VAULT              (11)

#define TEX_ID_PLAYER1            (12)
#define TEX_ID_PLAYER2            (13)
#define TEX_ID_PLAYER3            (14)
#define TEX_ID_PLAYER4            (15)

#define TEX_ID_SPRINTER1          (16)
#define TEX_ID_SPRINTER2          (17)
#define TEX_ID_SPRINTER3          (18)
#define TEX_ID_SPRINTER4          (19)

#define TEX_ID_RATINGSBG          (20)
#define TEX_ID_RATINGSFG          (21)
extern GLuint textureList[NUM_TEXTURES];

extern GLuint TEX_ID_LEVEL_THUMBS[LEVEL_COUNT];

int loadAssets(void);

#ifdef __cplusplus
}
#endif