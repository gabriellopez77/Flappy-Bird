#pragma once

#include "../GameObject.h"

class Button : public GameObject {
public:
	Button(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	bool clicked = false;

	void update() override;

	void checkMouseClick(double mouseX, double mouseY, int action);
};