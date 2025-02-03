#pragma once

#include "../Dependencies/ml/Sprite.h"

struct Collision {
	glm::vec2 size = glm::vec2(0.f);
	glm::vec2 position = glm::vec2(0.f);
};

class GameObject : public ml::Sprite {
public:
	~GameObject();

	void draw();
	virtual void update() {}

	void setAnimatedSprite(int posX, int posY, int width, int height, int count, float delay, float dt);

	// colisões
	Collision* collision = nullptr;

	static ml::Shader debugShader;

protected:
	float animationDelayTime = 0.f;
	unsigned short animationStage = 0;
};