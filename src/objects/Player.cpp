#include "Player.h"

#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../Dependencies/glad/glad.h"

#include <iostream>

#include "../Global.h"


Player::Player(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight
) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight)
{
}

void Player::draw() {
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.f));
	model = glm::rotate(model, 0.f, glm::vec3(0.f, 0.f, 1.f));


	model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.f));

	model = glm::scale(model, glm::vec3(size, 0.f));
	shader->setMat4(shader->modelLoc, model);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Player::update() {
	setAnimatedSprite(2, 487, 20, 20, 3, 0.03f);

	if (!gb::running) {
		position.y += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
		rotate += cos(static_cast<float>(glfwGetTime()) * 4.f) * 40 * gb::deltaTime;
		return;
	}


	// aplica as forcas	
	velocity.y += GRAVITY * gb::deltaTime;
	position += velocity * gb::deltaTime;


	// aplica a rota�ao do player
	rotate += glm::normalize(velocity).y * 220.f * gb::deltaTime;
	if (rotate > PLAYER_MAX_ROTATE)
		rotate = PLAYER_MAX_ROTATE;
	else if (rotate < PLAYER_MIN_ROTATE)
		rotate = PLAYER_MIN_ROTATE;


	// bordas
	if (position.y > gb::windowY - collSize.y - 165) {
		position.y = gb::windowY - collSize.y - 165;
		velocity.y = 0.f;
		gb::currentScreen = (int)ui::Death_screen;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y = 0;
		gb::currentScreen = (int)ui::Death_screen;
	}

	collPosition.x = position.x + 3;
	collPosition.y = position.y + 5;
}

bool Player::checkCollision(const GameObject* obj) const {
	return (collPosition.x + collSize.x >= obj->collPosition.x && collPosition.x <= obj->collPosition.x + obj->collSize.x &&
			collPosition.y + collSize.y >= obj->collPosition.y && collPosition.y <= obj->collPosition.y + obj->collSize.y);
}

void Player::input(Action action) {
	if (action == Action::JUMP) {
		velocity.y = -650.f;
		rotate = 10;
	}
}