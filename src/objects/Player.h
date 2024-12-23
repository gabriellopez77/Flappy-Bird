#pragma once

#include "../Dependencies/glm/glm.hpp"

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

	float rotate = 0.f;
	float scoreDelay = 0.f;
	unsigned short coinCount = 0;
	unsigned short matchCoinCount = 0;
	unsigned short score = 0;

	unsigned char skinType = 0;
};