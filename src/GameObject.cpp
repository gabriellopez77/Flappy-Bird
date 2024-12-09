#include "GameObject.h"

#include "../Dependencies/glad/glad.h"

Texture* GameObject::texture = nullptr;
Shader* GameObject::shader = nullptr;

unsigned int GameObject::VAO = 0;
unsigned int GameObject::VBO = 0;
unsigned int GameObject::EBO = 0;
unsigned int GameObject::VBO_TEX = 0;

glm::mat4 GameObject::model = glm::mat4(1.f);
std::vector<GameObject*> GameObject::objects = std::vector<GameObject*>();

const float GameObject::vertices[] = {
//  position
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
};

const unsigned int GameObject::indices[6] = { 0, 1, 3, 3, 2, 0 };

GameObject::GameObject(glm::ivec2* position, glm::vec2* size, glm::vec4 texCoords) :
	position(*position),
	size(*size) {

	this->texCoords = new float[8] {
		292.f / 512, 55.0f / 512,
		459.f / 512, 55.f / 512,
		292.f / 512, 0.0f / 512,
		459.f / 512, 0.0f  / 1512
	};

	objects.push_back(this);
}

void GameObject::draw() {
	shader->setMat4(shader->modelLoc, model);
	texture->use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void GameObject::create() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO_TEX);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}
void GameObject::update() {


	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::scale(model, glm::vec3(size, 0.f));
}

void GameObject::checkCollision(GameObject* obj) {
	//hipo = sqrt(powf(obj->position.x - position.x, 2) + powf(obj->position.y - position.y, 2));
}