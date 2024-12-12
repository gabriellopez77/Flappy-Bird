#include "Player.h"

#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include "../Global.h"

Player::Player(
	float radius,
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight
) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight) {
	this->radius = radius;
}

void Player::draw() {
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.f));
	model = glm::scale(model, glm::vec3(size, 0.f));
	
	shader->setMat4(shader->modelLoc, model);
	texture->use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Player::update() {
	// aplica as forcas
	velocity.y += 40;
	position += velocity * gb::deltaTime;


	// bordas
	if (position.x > gb::windowX - radius)
		position.x = gb::windowX - radius;

	if (position.x < 0)
		position.x = 0;

	if (position.y > gb::windowY - radius - 160) {
		position.y = gb::windowY - radius - 160;
		velocity.y = 0.f;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y = 0;
	}

	setAnimatedSprite(2, 487, 20, 20, 3, 0.03f);
}

bool pressed = false;
void Player::input(GLFWwindow* window, Action action) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!pressed) {
			gb::paused = !gb::paused;
			pressed = true;
		}
	}
	else pressed = false;

	if (action == Action::JUMP) {
		velocity.y = -650.f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->position.x += Xspeed * gb::deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->position.x -= Xspeed * gb::deltaTime;
}