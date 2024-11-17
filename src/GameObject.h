#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "player.h"
#include "vector"

class GameObject {
public:
	GameObject(Shader* shader, Texture* texture, glm::vec2* position, glm::vec2* size, float radius, bool isColored);
	void draw();
	void update();
	void checkCollisionPlayer(Player* obj);
	void checkCollision(GameObject* obj1);
	static void checkCollisionGlobal(Player* player);

	glm::mat4 model;

	glm::vec2 position;
	glm::vec2 size;

	Texture* texture;
	Shader* shader;

	float const maxSpeed = 1000;
	float const speed = 450;
	
	float cat1;
	float cat2;
	float hipo;
	float radius;

	bool isColored;

	float mass = 100.5f;
	glm::vec2 force = {0.f, 0.f};
	glm::vec2 velocity{ 0.f, 0.f };
	glm::vec2 gravity = glm::vec2(0.f, 9.81);

	static std::vector<GameObject*> objects;
};