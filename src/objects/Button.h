#pragma once

#include "../GameObject.h"

class Button : public GameObject {
public:
	Button(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	bool hover = false;

	void update() override;

	bool checkMouseClick(double mouseX, double mouseY, int action) const;
};