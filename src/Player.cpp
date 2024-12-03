#include "Player.h"

#include "iostream"
Player::Player(Shader* shader, float radius) : shader(shader) {
	position = glm::vec2(gb::windowX /2 - 50, gb::windowY /2 - 50);

	this->radius = radius;
}
void Player::draw() {
	shader->setBool(shader->isColoredLoc, false);
	shader->use();

	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.f));
	model = glm::scale(model, glm::vec3(100.f));
	shader->setMat4(shader->modelLoc, model);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Player::update() {
	// aplica as forcas

	force.y += mass * 9.81f;
	velocity += force * mass * gb::deltaTime;
	position += velocity * gb::deltaTime;


	// fricao do ar
	if (velocity.x > 0) {
		velocity.x += -0.5f;
		if (velocity.x < 0)
			velocity.x = 0;
	}

	if (velocity.x < 0) {
		velocity.x += 0.5f;
		if (velocity.x > 0)
			velocity.x = 0;
	}
	if (velocity.y > 0) {
		velocity.y += -0.5f;
		if (velocity.y < 0)
			velocity.y = 0;
	}

	if (velocity.y < 0) {
		velocity.y += 0.5f;
		if (velocity.y > 0)
			velocity.y = 0;
	}


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
	if (position.x > gb::windowX - 100) {
		position.x += gb::windowX - 100;
		velocity.x = -velocity.x;
	}

	if (position.x < 0) {
		position.x = 0;
		velocity.x = -velocity.x;
	}

	if (position.y + radius > gb::windowY) {
		position.y = gb::windowY - radius;
		velocity.y += -velocity.y;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y = -velocity.y;
	}
}
void Player::input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position.y += 20.f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		velocity.x += Xspeed * gb::deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		velocity.x += -Xspeed * gb::deltaTime;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		velocity.y += -Yspeed * gb::deltaTime;

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		velocity.y += Yspeed * gb::deltaTime;

}