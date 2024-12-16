#pragma once

#include "../GameObject.h"

#include <string>

class Text : public GameObject {
public:
	Text(int spriteX, int spriteY, int spriteWidth, int spriteHeight, char oneSpacing);

	void draw() override;

	glm::ivec4 sprites;

	glm::ivec2 tempPos = glm::ivec2(0.f);
	std::string text = "0";
	unsigned char oneSpacing;
};