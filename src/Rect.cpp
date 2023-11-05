#include "Rect.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

Rect::Rect(vec2 pos, float width, float height, bool isStatic, GLuint texture) 
 : Body(texture) {
	this->position = Vector2(pos[0], pos[1]);
	this->width  = width;
	this->height = height;
	this->isStatic = isStatic;
	mat4 iMatrix = GLM_MAT4_IDENTITY_INIT;
	vec3 scale = {height,height,1};
	glm_scale(iMatrix,scale);
	glm_mat4_copy(iMatrix,this->modelMatrix);
	this->updateMatrix();
}
float Rect::getWidth() {
	return this->width;
}
float Rect::getHeight() {
	return this->height;
}

void Rect::updateMatrix() {
	mat4 transformation = GLM_MAT4_IDENTITY_INIT;
	vec3 position = { this->position.x, this->position.y, 0.0 };
	glm_translate(transformation, position);

	float aspectRatio = static_cast<float>(wh) / ww;
	Vector2<float> scale = { aspectRatio * static_cast<float>(this->width), static_cast<float>(this->height) };
	vec3 transformScale = { scale.x, scale.y, 1.0 };
	glm_scale(transformation, transformScale);

	glm_mat4_copy(transformation, this->modelMatrix);
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
bool Rect::isColliding(Rect& bodyB) {
	Vector2<float> intersection = this->getIntersection(bodyB);
	return intersection.x <= 0 && intersection.y <= 0;
}
void Rect::translate(Vector2<float>& translation) {
	this->position += translation;
	this->updateMatrix();
}