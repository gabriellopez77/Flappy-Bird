#pragma once

#include "../../Dependencies/ml/Sprite.h"

class Button : public ml::Sprite {
public:
	void update();
	bool checkMouseClick(float mouseX, float mouseY) const;

	bool hover = false;
	bool enabled = true;
};