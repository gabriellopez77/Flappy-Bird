#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "vector"

class GameObject {
public:
	GameObject(glm::ivec2* position, glm::vec2* size, glm::vec4 texCoords);

	void draw();
	void update();
	void checkCollision(GameObject* obj1);
	static void create();

	glm::ivec2 position;
	glm::vec2 size;
	glm::vec4 texCoordsNormalized = glm::vec4(0.f);

	static Texture* texture;
	static Shader* shader;

	float* texCoords;
	static std::vector<GameObject*> objects;

protected:
	static unsigned int VAO, VBO, EBO, VBO_TEX;
	static const float vertices[8];
	static const unsigned int indices[6];
	static glm::mat4 model;
};