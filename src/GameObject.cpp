#include "GameObject.h"

#include "../Dependencies/glad/glad.h"

#include "global.h"

Texture* GameObject::texture = nullptr;
Shader* GameObject::shader = nullptr;

unsigned int GameObject::VAO = 0;
unsigned int GameObject::VBO = 0;
unsigned int GameObject::EBO = 0;
unsigned int GameObject::VBO_TEX = 0;

glm::mat4 GameObject::model = glm::mat4(1.f);

const float GameObject::vertices[] = {
//  position
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
};

const unsigned int GameObject::indices[6] = { 0, 1, 3, 3, 2, 0 };

GameObject::GameObject(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight
) {

	setNormalizedTexUV(spriteX, spriteY, spriteWidth, spriteHeight);
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

void GameObject::draw() {

	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::scale(model, glm::vec3(size, 0.f));

	shader->setMat4(shader->modelLoc, model);
	glBindTexture(GL_TEXTURE_2D, texture->ID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GameObject::setNormalizedTexUV(int spriteX, int spriteY, int spriteWidth, int spriteHeight) {

	texCoords[0] = spriteX / 512.f;					 texCoords[7] = (spriteY + spriteHeight) / 512.f;
	texCoords[2] = (spriteX + spriteWidth) / 512.f;	 texCoords[5] = (spriteY + spriteHeight) / 512.f;
	texCoords[4] = spriteX / 512.f;					 texCoords[3] = spriteY / 512.f;
	texCoords[6] = (spriteX + spriteWidth) / 512.f;   texCoords[1] = spriteY / 512.f;
}

void GameObject::setAnimatedSprite(int spriteX, int spriteY, int spriteWidth, int spriteHeight, int imagesCount, float delay) {
	animationDelay += gb::deltaTime;

	if (animationDelay >= delay) {
		setNormalizedTexUV(spriteX += (spriteWidth * animationStage), spriteY, spriteWidth, spriteHeight);
		animationDelay = 0.f;
		animationStage++;

		if (animationStage == imagesCount)
			animationStage = 0;
	}
}

void GameObject::checkCollision(GameObject* obj) {
	//hipo = sqrt(powf(obj->position.x - position.x, 2) + powf(obj->position.y - position.y, 2));
}