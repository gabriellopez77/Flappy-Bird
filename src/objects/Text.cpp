#include "Text.h"

#include "../../Dependencies/glad/glad.h"

Text::Text(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight,
	char oneSpacing
) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight)
{
	sprites = glm::ivec4(spriteX, spriteY, spriteWidth, spriteHeight);
	this->oneSpacing = oneSpacing;
}

void Text::draw() {
	tempPos = position;

	for (auto c = 0; c < text.size(); c++) {
		int value;
		switch (text[c]) {
			case '0': value = 0; break;
			case '1': value = 1; break;
			case '2': value = 2; break;
			case '3': value = 3; break;
			case '4': value = 4; break;
			case '5': value = 5; break;
			case '6': value = 6; break;
			case '7': value = 7; break;
			case '8': value = 8; break;
			case '9': value = 9; break;
			default: value = 10; break;
		}

		setNormalizedTexUV(sprites.x + (sprites.z * value), sprites.y, sprites.z, sprites.w);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(tempPos, 0.f));
		model = glm::scale(model, glm::vec3(size, 0.f));
		
		shader->setMat4(shader->modelLoc, model);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		tempPos.x += value == 1 ? size.x - oneSpacing : size.x;
	}
}