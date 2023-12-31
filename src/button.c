#include "button.h"

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
	return butt;
}

void deleteButton(button *b)
{
	if(b) free(b);
}

buttonState getButtonState(button *butt)
{
	return butt->state;
}

int getButtonX(button *butt)
{
	return butt->x;
}

int getButtonY(button *butt)
{
	return butt->y;
}

int getButtonW(button *butt)
{
	return butt->w;
}

int getButtonH(button *butt)
{
	return butt->h;
}

void placeButton(button *butt, int x, int y)
{
	butt->x = x;
	butt->y = y;
}

void recreateButton(button *butt, int x, int y, int w, int h)
{
	butt->x = x;
	butt->y = y;
	butt->w = w;
	butt->h = h;
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

buttonState updateButton(button *butt)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
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
	vec3 translate = {0};
	translate[0] = (2*b->x / (float)ww) - 1;
	translate[1] = (-2*b->y / (float)wh) + 1;
	glm_translate(matrix,translate);
	glm_scale(matrix,(vec3){(2*b->w/(float)ww),(2*b->h/(float)wh),1});
}

GLuint getButtonTexture(button *b)
{
	return b->texture;
}