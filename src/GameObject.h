#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Texture.h"

class GameObject {
public:
	GameObject(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	static void create();

	virtual void draw();
	virtual void update() {}

	void setNormalizedTexUV(int spriteX, int spriteY, int spriteWidth, int spriteHeight);
	void setAnimatedSprite(int spriteX, int spriteY, int spriteWidth, int spriteHeight, int imagesCount, float delay);

	// transforms
	glm::vec2 position =			glm::vec2(0);
	glm::ivec2 size =				glm::ivec2(0);

	// colisoes
	glm::vec2 collPosition =		glm::vec2(0.f);
	glm::vec2 collSize =			glm::vec2(0.f);

	static Texture* texture;
	static Shader* shader;

	float texCoords[8];

protected:

	float animationDelay = 0.f;
	unsigned short animationStage = 0;

	static unsigned int VAO, VBO, EBO, VBO_TEX;
	static const float vertices[8];
	static const unsigned int indices[6];
	static glm::mat4 model;
};