#pragma once

#include "../Dependencies/glm/glm.hpp"

//#include "../Dependencies/glfw/glfw3.h"

#include "../GameObject.h"

enum class Action : char { JUMP, EMPTY };
class Player : public GameObject {
public:
	Player(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw() override;
	void update() override;
	void input(Action action);
	bool checkCollision(const GameObject* obj) const;

	glm::vec2 velocity = glm::vec2(0.f);

	float maxSpeed = 1000.f;
	float Xspeed = 900.f;
	float Yspeed = 900.f;
	float rotate = 0.f;
	unsigned short coinCount = 0;
	bool pressed = false;
};