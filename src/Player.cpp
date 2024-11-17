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

	//force.y += mass * 9.81f;
	velocity += force * mass * gb::deltaTime;
	position += force * gb::deltaTime;


	// fricao do ar
	if (force.x > 0) {
		force.x += -0.5f;
		if (force.x < 0)
			force.x = 0;
	}

	if (force.x < 0) {
		force.x += 0.5f;
		if (force.x > 0)
			force.x = 0;
	}
	if (force.y > 0) {
		force.y += -0.5f;
		if (force.y < 0)
			force.y = 0;
	}

	if (force.y < 0) {
		force.y += 0.5f;
		if (force.y > 0)
			force.y = 0;
	}


	// define a velocidade maxima
	if (force.x > maxSpeed)
		force.x = maxSpeed;

	else if (force.x < -maxSpeed)
		force.x = -maxSpeed;


	if (force.y > maxSpeed)
		force.y = maxSpeed;

	else if (force.y < -maxSpeed)
		force.y = -maxSpeed;


	// bordas
	if (position.x > gb::windowX - 100) {
		position.x = gb::windowX - 100;
		force.x = -force.x;
	}
	else if (position.x < 0) {
		position.x = 0;
		force.x = -force.x;
	}

	if (position.y > gb::windowY - 100) {
		position.y = gb::windowY - 100;
		force.y = -force.y;
	}

	else if (position.y < 0) {
		position.y = 0;
		force.y = -force.y;
	}
}
void Player::input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		force.x += Xspeed * gb::deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		force.x += -Xspeed * gb::deltaTime;
	}

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		force.y += -Yspeed * gb::deltaTime;

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		force.y += Yspeed * gb::deltaTime;

}