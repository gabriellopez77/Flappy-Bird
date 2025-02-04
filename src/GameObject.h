#pragma once

#include "../Dependencies/ml/Sprite.h"

struct Collision {
	glm::vec2 size = glm::vec2(-1.f);
	glm::vec2 position = glm::vec2(-1.f);
};

class GameObject : public ml::Sprite {
public:

	void draw();
	virtual void update() {}

	// colisões
	Collision collision;
};