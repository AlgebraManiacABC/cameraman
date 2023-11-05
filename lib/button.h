#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "render.h"
#include <stdbool.h>

#define BUTTON_INACTIVE 0
#define BUTTON_HELD 1
#define BUTTON_ACTIVATED 2

/**
 * A button is a special type with a physical presence on the screen,
 * given by the x and y positon of the middle of the button, and its
 * width and height.
 * It must be rendered with `renderButton()`.
 * 
 * These buttons have multiple states: Inactive, Held, Activated
 * It is the user's job to detect these states and deal with events.
 * The button's state can be updated with `buttonUpdate()`, which
 * takes the current mouse position and state, and updates the button's
 * state, if applicable. These particular buttons are only responsive
 * to left clicks within the button's area, and are only activated when
 * the left mouse button is released while over a currently held button.
 * A button is held only if the left mouse button is held over it, and
 * returns to an inactive state if the mouse leaves the area before releasing.
 * 
 * They also have an inherent size and position on screen, in pixels.
 * This is provided when initialized.
 */
typedef struct button button;

/**
 * `BUTTON_INACTIVE` - Button is inactive
 * `BUTTON_HELD` - Button is being held, but is not activated
 * `BUTTON_ACTIVATED` - Button has been released and is active
 */
typedef Uint8 buttonState;

button *createButton(int x, int y, int w, int h, GLuint texture);
buttonState getButtonState(button *b);

int getButtonX(button *b);
int getButtonY(button *b);
int getButtonW(button *b);
int getButtonH(button *b);

bool mouseOverButton(button *b, int mouseX, int mouseY);

buttonState updateButton(button *b, int mouseX, int mouseY, Uint32 mouseState);
void deactivateButton(button *b);

void getButtonMatrix(button *b, mat4 matrix);

GLuint getButtonTexture(button *b);

#ifdef __cplusplus
}
#endif

#endif