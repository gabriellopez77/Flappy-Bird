#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "vector"

class GameObject {
public:
	GameObject(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw();
	virtual void update() {}
	void checkCollision(GameObject* obj1);
	void setNormalizedTexUV(int spriteX, int spriteY, int spriteWidth, int spriteHeight);
	static void create();

	glm::ivec2 position = glm::ivec2(0.f);
	glm::ivec2 size = glm::ivec2();
	glm::vec4 texCoordsNormalized = glm::vec4(0.f);

	static Texture* texture;
	static Shader* shader;

	float texCoords[8]{ 0.f };

protected:
	static unsigned int VAO, VBO, EBO, VBO_TEX;
	static const float vertices[8];
	static const unsigned int indices[6];
	static glm::mat4 model;
};