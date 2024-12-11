#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"

#include "Shader.h"
#include "global.h"
#include "GameObject.h"


class Player : public GameObject {
public:
	Player(float radius, int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw() override;
	void input(GLFWwindow* window);
	void update() override;

	glm::ivec2 position = glm::ivec2(0.f);
	glm::ivec2 size = glm::ivec2(0.f);
	glm::vec2 velocity = glm::vec2(0.f);

	float maxSpeed = 1000.f;
	float Xspeed = 900.f;
	float Yspeed = 900.f;
	float radius;
};