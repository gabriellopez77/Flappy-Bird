#pragma once

#include "../InterfaceObject.h"
#include "../GameObject.h"
#include "../objects/Text.h"

class Hud : public InterfaceObject {
public:
	Hud();

	void update() override;
	void draw() override;

	GameObject coin_image;
	Text coinCount_text;
	Text score_text;
};
