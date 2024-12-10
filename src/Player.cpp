#include "Player.h"

#include "../Dependencies/glm/gtc/matrix_transform.hpp"


#include "iostream"
Player::Player(
	float radius,
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight
) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight) {
	this->position = glm::vec2(gb::windowX /2 - 50, gb::windowY /2 - 50);

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

float delay = 0.f;
void Player::update() {

	// aplica as forcas
	velocity.y += 40;
	position += velocity * gb::deltaTime;

	delay += gb::deltaTime;

	if (delay <= 0.33)
		setNormalizedTexUV(2, 487, 20, 20);
	else if (delay > 0.33f && delay <= 0.66f)
		setNormalizedTexUV(30, 487, 20, 20);
	else if (delay > 0.66f && delay <= 1.f)
		setNormalizedTexUV(58, 487, 20, 20);
	else delay = 0.f;


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
}
bool pressed = false;
void Player::input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!pressed) {
			pressed = true;
			velocity.y = -750.f;
		}
	}
	else pressed = false;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->position.x += Xspeed * gb::deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->position.x -= Xspeed * gb::deltaTime;
}