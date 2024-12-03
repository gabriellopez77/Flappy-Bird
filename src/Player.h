#pragma once

#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "global.h"


class Player {
public:
	Player(Shader* shader, float radius);

	void draw();
	void input(GLFWwindow* window);
	void update();

	Shader* shader;
	glm::vec2 position;
	glm::vec2 force;
	glm::vec2 velocity;


	float maxSpeed = 1000.f;
	float Xspeed = 900.f;
	float Yspeed = 900.f;
	float radius;
	float mass = 10.f;

	unsigned int textureID;
};