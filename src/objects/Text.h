#pragma once

#include "../../Dependencies/ml/Sprite.h"

#include <string>

class Text : public ml::Sprite {
public:
	Text(int posX, int posY, int width, int height, char oneSpacing);

	void draw() override;

	glm::ivec4 sprites;

	glm::ivec2 tempPos;
	std::string text = "0";
	unsigned char oneSpacing;
};