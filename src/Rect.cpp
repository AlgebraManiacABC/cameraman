#include "Rect.h"
#include "Vector2.h"
#include "cglm/cglm.h"

Rect::Rect(vec2 pos, float width, float height, bool isStatic, GLuint texture, GLuint buffer) 
 : Body(texture, buffer) {
	this->position = Vector2(pos[0], pos[1]);
	this->width  = width;
	this->height = height;
	this->isStatic = isStatic;
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