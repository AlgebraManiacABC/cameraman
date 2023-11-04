#include "../lib/Rect.h"
#include "../lib/Vector2.h"

Rect::Rect(Vector2<float> pos, float width, float height, bool isStatic, GLuint texture, GLuint buffer) 
 : Body(pos, texture, buffer) {
	this->position = pos;
	this->width  = width;
	this->height = height;
	this->isStatic = isStatic;

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
Vector2<float> Rect::getIntersection(Rect& bodyB) {
	Vector2<float>& positionA = this->getPosition();
	int widthA = this->getWidth();
	int heightA = this->getHeight();

	Vector2<float>& positionB = bodyB.getPosition();
	int widthB = bodyB.getWidth();
	int heightB = bodyB.getHeight();

	Vector2<float> distance = positionA - positionB;
	distance.abs();
	distance.x -= (widthA  + widthB)  * 0.5;
	distance.y -= (heightA + heightB) * 0.5;

	return distance;
}
bool Rect::isColliding(Rect& bodyB) {
	Vector2<float> distance = this->getIntersection(bodyB);
	return distance.x <= 0 || distance.y <= 0;
}