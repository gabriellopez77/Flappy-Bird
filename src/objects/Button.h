#pragma once

#include "../GameObject.h"

class Button : public GameObject {
public:
	Button(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void update() override;
	bool checkMouseClick(double mouseX, double mouseY) const;

	bool hover = false;
	bool enabled = true;
};