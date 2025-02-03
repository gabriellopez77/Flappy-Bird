#include "GameObject.h"

#include "../Dependencies/glad/glad.h"

#include "Global.h"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

ml::Shader GameObject::debugShader(nullptr, nullptr);

GameObject::~GameObject() {
	delete collision;
}

void GameObject::draw() {
	Sprite::draw();

	//glUseProgram(debugShader.id);
	//// desenha as hitbox
	//if (gb::debugMode && collision) {
	//	model = glm::mat4(1.f);
	//	model = glm::translate(model, glm::vec3(collision->position, 0.f));
	//	model = glm::scale(model, glm::vec3(collision->size, 0.f));

	//	glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, &model[0][0]);

	//	glUniform4fv(glGetUniformLocation(shader.id, "hitBoxColor"), 1, &hitBoxColor[0]);

	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//}
}

void GameObject::setAnimatedSprite(int posX, int posY, int width, int height, int count, float delay, float dt) {
	animationDelayTime += dt;
	useTexture = true;

	if (animationDelayTime >= delay) {
		animationDelayTime = 0.f;
		setNormalizedTex(posX += (width * animationStage), posY, width, height);
		animationStage++;

		if (animationStage == count)
			animationStage = 0;
	}
}