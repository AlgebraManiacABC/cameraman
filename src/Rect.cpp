#include "../lib/Rect.h"
#include "../lib/Vector2.h"

Rect::Rect(Vector2<float> pos, float width, float height, GLuint texture, GLuint buffer) 
 : Body(pos, texture, buffer) {
	this->position = pos;
	this->width  = width;
	this->height = height;

	this->vertices = {
		{ -width/2, -height/2 },
		{ -width/2,  height/2 },
		{  width/2,  height/2 },
		{  width/2, -height/2 },
	};
}
int Rect::getWidth() {
	return this->width;
}
int Rect::getHeight() {
	return this->height;
}