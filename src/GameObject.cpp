#include "GameObject.h"

#include "../Dependencies/glad/glad.h"

#include "Global.h"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>


void GameObject::draw() {
	Sprite::draw();

	// desenha as hitbox
	if (gb::debugMode && collision.position.x != -1) {
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(collision.position, 0.f));
		model = glm::scale(model, glm::vec3(collision.size, 0.f));

		glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniform1i(shader.useTextureLoc, false);
		glUniform1f(shader.alphaLoc, hitBoxColor.w);
		glUniform3fv(shader.colorLoc, 1, &hitBoxColor[0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}