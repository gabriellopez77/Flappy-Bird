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
	int textSize = text.size();
	char currentChar;
	for (int c = 0; c < textSize; c++) {
		int value;
		currentChar = text[c];
		if (currentChar >= '0' && currentChar <= '9')
			value = currentChar - '0';
		else value = -1;

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