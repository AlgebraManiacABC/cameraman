#include "Player.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "main.h"
#include "render.h"
#include "events.h"
#include "assets.h"
#include "Rect.h"
#include "game.h"

Player::Player(vec2 position) : body { position, 0.125, 0.25, false, textureList[TEX_ID_CAMERAMAN_R1] } {
	this->moveSpeed = 1.0;
}

void Player::updateControls(Uint32 buttonsHeld) {
	this->controls.up    = static_cast<bool>(buttonsHeld & HOLDING_W);
	this->controls.down  = static_cast<bool>(buttonsHeld & HOLDING_S);
	this->controls.left  = static_cast<bool>(buttonsHeld & HOLDING_A);
	this->controls.right = static_cast<bool>(buttonsHeld & HOLDING_D);
}
void Player::update(Uint32 buttonsHeld) {
	this->updateControls(buttonsHeld);
	Vector2<float>& velocity = this->body.getVelocity();
	Vector2<float> movement { (this->controls.right - this->controls.left) * this->moveSpeed, 0 };
	movement.x -= velocity.x * 0.5;

	velocity += movement;
}