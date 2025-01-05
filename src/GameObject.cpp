#include "GameObject.h"

#include "../Dependencies/glad/glad.h"

#include "Global.h"

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
)
{
	setNormalizedTexUV(spriteX, spriteY, spriteWidth, spriteHeight);
}
GameObject::GameObject(bool tex) {};

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

	glUniformMatrix4fv(shader->modelLoc, 1, GL_FALSE, &model[0][0]);
	glUniform1f(shader->alphaLoc, alpha);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);
	glUniform1i(glGetUniformLocation(shader->ID, "debugMode"), false);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// desenha as hitbox
	if (gb::debugMode && collision) {
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(collision->position, 0.f));
		model = glm::scale(model, glm::vec3(collision->size, 0.f));

		glUniformMatrix4fv(shader->modelLoc, 1, GL_FALSE, &model[0][0]);

		glUniform1i(shader->debugModeLoc, true);
		glUniform4fv(shader->hitBoxColorLoc, 1, &hitBoxColor[0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void GameObject::setNormalizedTexUV(int spriteX, int spriteY, int spriteWidth, int spriteHeight) {
	texCoords[0] = spriteX / 512.f;					 texCoords[7] = (spriteY + spriteHeight) / 512.f;
	texCoords[2] = (spriteX + spriteWidth) / 512.f;	 texCoords[5] = (spriteY + spriteHeight) / 512.f;
	texCoords[4] = spriteX / 512.f;					 texCoords[3] = spriteY / 512.f;
	texCoords[6] = (spriteX + spriteWidth) / 512.f;  texCoords[1] = spriteY / 512.f;
}

void GameObject::setAnimatedSprite(int spriteX, int spriteY, int spriteWidth, int spriteHeight, int spritesCount, float delay) {
	animationDelayTime += gb::deltaTime;

	if (animationDelayTime >= delay) {
		animationDelayTime = 0.f;
		setNormalizedTexUV(spriteX += (spriteWidth * animationStage), spriteY, spriteWidth, spriteHeight);
		animationStage++;

		if (animationStage == spritesCount)
			animationStage = 0;
	}
}