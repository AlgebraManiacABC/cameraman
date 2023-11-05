#include "Rect.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "main.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

Rect::Rect(vec3 pos, float width, float height, bool isStatic, bool hasCollisions, GLuint texture) 
 : Body(texture) {
	this->position = Vector2(pos[0], pos[1]);
	this->hasCollisions = hasCollisions;
	this->depth = pos[2];
	this->width  = width;
	this->height = height;
	this->isStatic = isStatic;
	mat4 iMatrix = GLM_MAT4_IDENTITY_INIT;
	vec3 scale = {height,height,1};
	glm_scale(iMatrix,scale);
	glm_mat4_copy(iMatrix,this->modelMatrix);
}
float Rect::getWidth() {
	return this->width;
}
float Rect::getHeight() {
	return this->height;
}

Vector2<float> Rect::getIntersection(Rect& bodyB) {
	Vector2<float>& positionA = this->getPosition();
	float widthA = this->getWidth();
	float heightA = this->getHeight();

	Vector2<float>& positionB = bodyB.getPosition();
	float widthB = bodyB.getWidth();
	float heightB = bodyB.getHeight();

	Vector2<float> distance = positionA - positionB;
	distance.abs();
	distance.x -= (widthA  + widthB)  * 0.5;
	distance.y -= (heightA + heightB) * 0.5;

	return distance;
}
Vector2<float> Rect::getSignedIntersection(Rect& bodyB) {
	Vector2<float> intersection = this->getIntersection(bodyB);
	Vector2<float> relativePosition = bodyB.getPosition() - this->getPosition();
	float signX = copysign(1.0, relativePosition.x);
	float signY = copysign(1.0, relativePosition.y);
	return { intersection.x * signX, intersection.y * signY };
}
bool Rect::isColliding(Rect& bodyB) {
	Vector2<float> intersection = this->getIntersection(bodyB);
	return intersection.x <= 0 && intersection.y <= 0;
}
void Rect::translate(Vector2<float>& translation) {
	this->position += translation;
}
