#include "Player.h"

#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glad/glad.h"

#include <iostream>

#include "../Global.h"


Player::Player(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight
) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight)
{
	collision = new Collision();
}

void Player::draw() {
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.f));
	model = glm::rotate(model, 0.f, glm::vec3(0.f, 0.f, 1.f));

	model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.f));

	model = glm::scale(model, glm::vec3(size, 0.f));
	glUniformMatrix4fv(shader->modelLoc, 1, GL_FALSE, &model[0][0]);

	glUniform1i(glGetUniformLocation(shader->ID, "debugMode"), false);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// desenha as hitbox
	if (gb::debugMode) {
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(collision->position, 0.f));
		model = glm::scale(model, glm::vec3(collision->size, 0.f));

		glUniformMatrix4fv(shader->modelLoc, 1, GL_FALSE, &model[0][0]);

		glUniform1i(shader->debugModeLoc, true);
		glUniform4fv(shader->hitBoxColorLoc, 1, &hitBoxColor[0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Player::update() {
	if (gb::currentStatus != status::Dead)
		setAnimatedSprite(2 + (60 * skinType), 487, 20, 20, 3, 0.03f);


	if (gb::currentStatus == status::notStarted || gb::currentStatus == status::Starting) {
		position.y += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
		rotate += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
		return;
	}

	else if (gb::currentStatus == status::Started || gb::currentStatus == status::Dead && !groundCollided) {
		// aplica a gravidade
		velocity += GRAVITY * gb::deltaTime;
		position.y += velocity * gb::deltaTime;
	
		// atualiza a hitbox do jogador
		collision->position.y = position.y;

		// rotaçao do player
		rotate += glm::normalize(glm::vec2(velocity)).y * 220.f * gb::deltaTime;
		if (rotate > PLAYER_MAX_ROTATE)
			rotate = PLAYER_MAX_ROTATE;
		else if (rotate < PLAYER_MIN_ROTATE)
			rotate = PLAYER_MIN_ROTATE;

	}
}

bool Player::checkCollision(const GameObject* obj) const {
	return (collision->position.x + collision->size.x >= obj->collision->position.x && collision->position.x <= obj->collision->position.x + obj->collision->size.x &&
			collision->position.y + collision->size.y >= obj->collision->position.y && collision->position.y <= obj->collision->position.y + obj->collision->size.y);
}

void Player::input(action action) {
	if (action == action::JUMP) {
		velocity = -650.f;
		rotate = 10;
	}
}