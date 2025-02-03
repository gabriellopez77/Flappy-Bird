#pragma once

#include "../../Dependencies/ml/Sprite.h"
#include "../objects/Text.h"
#include "../objects/Button.h"
#include "../InterfaceObject.h"

class Death_screen : public InterfaceObject {
public:
	Death_screen();

	void update() override;
	void draw() override;
	void start() override;

	ml::Sprite gameOver_image;
	ml::Sprite panel_image;
	Text playerBestScore_text;
	Text playerScore_text;
	Text coinCount_text;
	Button respawn_button;
	Button house_button;
};