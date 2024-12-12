#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"

#include "../GameObject.h"

enum class Action : char { JUMP, EMPTY };
class Player : public GameObject {
public:
	Player(float radius, int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw() override;
	void input(GLFWwindow* window, Action action);
	void update() override;

	glm::vec2 velocity = glm::vec2(0.f);

	unsigned short coinCount = 0;

	float maxSpeed = 1000.f;
	float Xspeed = 900.f;
	float Yspeed = 900.f;
	float radius;
};