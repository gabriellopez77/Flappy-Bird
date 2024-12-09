#include "Player.h"

#include "../Dependencies/glm/gtc/matrix_transform.hpp"


#include "iostream"
Player::Player(float radius, glm::ivec2* position, glm::vec2* size, glm::vec4 texCoords) : GameObject(position, size, texCoords) {
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

void Player::update() {
	// aplica as forcas

	velocity.y += 40;
	position += velocity * gb::deltaTime;



	// define a velocidade maxima
	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;

	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;


	if (velocity.y > maxSpeed)
		velocity.y = maxSpeed;

	else if (velocity.y < -maxSpeed)
		velocity.y = -maxSpeed;


	// bordas
	if (position.x > gb::windowX - radius)
		position.x = gb::windowX - radius;

	if (position.x < 0)
		position.x = 0;

	if (position.y > gb::windowY - radius) {
		position.y = gb::windowY - radius;
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