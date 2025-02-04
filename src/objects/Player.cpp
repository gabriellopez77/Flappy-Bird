#include "Player.h"

#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glad/glad.h"

#include "../Global.h"


Player::Player() {
	size = glm::vec2(PLAYER_SIZE);
	position = PLAYER_START_POSITION;

	collision.size = glm::vec2(50, 40);
	collision.position.x = position.x + 3.f;
	collision.position.y = position.y + 5.f;

	gb::player = this;
}

void Player::update() {
	if (gb::currentStatus != status::Dead)
		setAnimatedSprite(2 + (60 * skinType), 487, 20, 20, 3, 0.03f, gb::deltaTime);


	if (gb::currentStatus == status::notStarted) {
		position.y += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
		rotate += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
	}

	else if (gb::currentStatus == status::Started || (gb::currentStatus == status::Dead && !groundCollided)) {
		// aplica a gravidade
		velocity += GRAVITY * gb::deltaTime;
		position.y += velocity * gb::deltaTime;

		// verifica se o jogador de bateu no "teto"
		if (collision.position.y <= 0.f) {
			position.y = 0.f;
			gb::currentStatus = status::Dead;
		}
	
		// atualiza a hitbox do jogador
		collision.position.y = position.y + 5.f;

		// rotaçao do player
		rotate += glm::normalize(glm::vec2(velocity)).y * 220.f * gb::deltaTime;
		if (rotate > PLAYER_MAX_ROTATE)
			rotate = PLAYER_MAX_ROTATE;
		else if (rotate < PLAYER_MIN_ROTATE)
			rotate = PLAYER_MIN_ROTATE;
	}
}

bool Player::checkCollision(const GameObject* obj) const {
	return (collision.position.x + collision.size.x >= obj->collision.position.x && collision.position.x <= obj->collision.position.x + obj->collision.size.x &&
			collision.position.y + collision.size.y >= obj->collision.position.y && collision.position.y <= obj->collision.position.y + obj->collision.size.y);
}

void Player::input(action action) {
	if (action == action::JUMP) {
		velocity = -650.f;
		rotate = 10;
	}
}