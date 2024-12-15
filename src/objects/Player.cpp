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
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.f));
	model = glm::rotate(model, 0.f, glm::vec3(0.f, 0.f, 1.f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
	model = glm::scale(model, glm::vec3(size, 0.f));
	
	shader->setMat4(shader->modelLoc, model);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Player::update() {
	// aplica as forcas
	velocity.y += GRAVITY * gb::deltaTime;
	position += velocity * gb::deltaTime;


	// aplica a rotaçao do player
	rotate += glm::normalize(velocity).y * 170.f * gb::deltaTime;
	if (rotate > PLAYER_MAX_ROTATE)
		rotate = PLAYER_MAX_ROTATE;
	else if (rotate < PLAYER_MIN_ROTATE)
		rotate = PLAYER_MIN_ROTATE;

	// bordas
	if (position.x > gb::windowX - PLAYER_SIZE)
		position.x = gb::windowX - PLAYER_SIZE;

	if (position.x < 0)
		position.x = 0;

	if (position.y > gb::windowY - PLAYER_SIZE - 160) {
		position.y = gb::windowY - PLAYER_SIZE - 160;
		velocity.y = 0.f;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y = 0;
	}

	setAnimatedSprite(2, 487, 20, 20, 3, 0.03f);
}

bool Player::checkCollision(const GameObject* obj) const {
	return (obj->position.x >= position.x && obj->position.x + obj->size.x <= position.x + size.x &&
			obj->position.y >= position.y && obj->position.y + obj->size.y <= position.y + size.y);
}

void Player::input(Action action) {
	if (glfwGetKey(gb::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!pressed) {
			gb::paused = !gb::paused;
			pressed = true;
		}
	}
	else pressed = false;

	if (action == Action::JUMP) {
		velocity.y = -650.f;
		rotate = 10;
	}

	if (glfwGetKey(gb::window, GLFW_KEY_D) == GLFW_PRESS)
		this->position.x += Xspeed * gb::deltaTime;

	if (glfwGetKey(gb::window, GLFW_KEY_A) == GLFW_PRESS)
		this->position.x -= Xspeed * gb::deltaTime;
}