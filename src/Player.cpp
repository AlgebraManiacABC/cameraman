#include "Player.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "main.h"
#include "render.h"
#include "events.h"
#include "assets.h"
#include "Rect.h"
#include "game.h"
#include "Rect.h"
#include <functional>
#include "Event.h"
#include "AngleDiff.h"
#include <cmath>


Player::Player(vec2 position) : body { position, 0.125, 0.25, false, true, textureList[TEX_ID_CAMERAMAN_R1] } {
	this->moveSpeed = 1.0;
	this->jumpHeight = 4.0;
	this->score = 0;

	this->canJump = true;
	this->onCollision = Event([this](Collision collision) {
		int sign = (collision.bodyA == &this->body) ? -1 : 1;
		if (collision.normal.y * sign > 0) {
			this->canJump = true;
		}
	});
	this->body.onCollision = &this->onCollision;
}

void Player::updateControls(Uint32 buttonsHeld) {
	this->controls.up    = static_cast<bool>(buttonsHeld & HOLDING_W);
	this->controls.down  = static_cast<bool>(buttonsHeld & HOLDING_S);
	this->controls.left  = static_cast<bool>(buttonsHeld & HOLDING_A);
	this->controls.right = static_cast<bool>(buttonsHeld & HOLDING_D);
}
void Player::updateCameraAngle() {
	constexpr float PI = 3.14159265;
	SDL_GetGlobalMouseState(&this->mouse.x, &this->mouse.y);
	Vector2<float> mousePlayerDistance = this->body.distanceToScreen(this->mouse);
	float cameraAngle = std::atan2(mousePlayerDistance.y, mousePlayerDistance.x);
	
	Vector2<float> playerTargetDistance = this->body.getPosition() - this->target->getPosition();
	float targetAngle = std::atan2(playerTargetDistance.y, playerTargetDistance.x);

	float angleDifference = std::fmod((angleDiff(targetAngle, cameraAngle) + PI), (2.0f * PI));

	char buffer[512] = {0};
	sprintf(buffer, "%0.2f", angleDifference);
	SDL_SetWindowTitle(w, buffer);
}
void Player::update(Uint32 buttonsHeld) {
	this->updateControls(buttonsHeld);
	this->updateCameraAngle();
	Vector2<float>& velocity = this->body.getVelocity();
	Vector2<float> movement { (this->controls.right - this->controls.left) * this->moveSpeed, 0 };
	movement.x -= velocity.x * 0.5;

	if (controls.up && this->canJump) {
		this->canJump = false;
		movement.y += this->jumpHeight;
	}

	velocity += movement;
}