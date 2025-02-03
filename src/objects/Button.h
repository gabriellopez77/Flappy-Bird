#pragma once

#include "../../Dependencies/ml/Sprite.h"

class Button : public ml::Sprite {
public:
	void update();
	bool checkMouseClick(double mouseX, double mouseY) const;

	bool hover = false;
	bool enabled = true;
};