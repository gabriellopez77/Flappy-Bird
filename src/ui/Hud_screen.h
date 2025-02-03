#pragma once

#include "../../Dependencies/ml/Sprite.h"
#include "../InterfaceObject.h"
#include "../objects/Text.h"
#include "../objects/Button.h"

class Hud : public InterfaceObject {
public:
	Hud();

	void update() override;
	void draw() override;
	void start() override;

	ml::Sprite coin_image;
	Button pause_button;
	Text coinCount_text;
	Text score_text;
};
