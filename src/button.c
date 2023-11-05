#include "button.h"
#include <cglm/cglm.h>

struct button
{
	int x, y;
	int w, h;
	buttonState state;
	GLuint texture;
};

button *createButton(int x, int y, int w, int h, GLuint texture)
{
	button *butt = malloc(sizeof(button));
	butt->x = x;
	butt->y = y;
	butt->w = w;
	butt->h = h;
	butt->state = BUTTON_INACTIVE;
	butt->texture = texture;
}

buttonState getButtonState(button *butt)
{
	return butt->state;
}

int getButtonX(button *butt)
{
	butt->x;
}

int getButtonY(button *butt)
{
	butt->y;
}

int getButtonW(button *butt)
{
	butt->w;
}

int getButtonH(button *butt)
{
	butt->h;
}

bool mouseOverButton(button *butt, int mouseX, int mouseY)
{
	if(mouseX <= butt->x + (butt->w/2) && mouseX >= butt->x - (butt->w/2))
	{
		if(mouseY <= butt->y + (butt->h/2) && mouseY >= butt->y - (butt->h/2))
		{
			return true;
		}
	}
	return false;
}

buttonState updateButton(button *butt, int mouseX, int mouseY, Uint32 mouseState)
{
	switch(butt->state)
	{
		case BUTTON_INACTIVE:
			if(mouseState & SDL_BUTTON_LEFT && mouseOverButton(butt, mouseX, mouseY))
			{
				// Left mouse button held while over inactive button
				butt->state = BUTTON_HELD;
			}
			break;
		case BUTTON_HELD:
			if(mouseOverButton(butt,mouseX,mouseY))
			{
				if(!(mouseState & SDL_BUTTON_LEFT))
				{
					//	Left mouse button released while over held button
					butt->state = BUTTON_ACTIVATED;
				}
			}
			else
			{
				butt->state = BUTTON_INACTIVE;
			}
			break;
		case BUTTON_ACTIVATED:
			//	Don't deactivate a button without user approval.
			break;
	}
	return butt->state;
}

void deactivateButton(button *butt)
{
	if(!butt) return;
	butt->state = BUTTON_INACTIVE;
}

void getButtonMatrix(button *b, mat4 matrix)
{
	glm_mat4_copy(GLM_MAT4_IDENTITY,matrix);
	glm_translate(matrix,(vec3){b->x,b->y,0});
	glm_scale(matrix,(vec3){b->w,b->h,1});
}

GLuint getButtonTexture(button *b)
{
	return b->texture;
}