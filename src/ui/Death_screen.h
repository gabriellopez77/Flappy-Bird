#pragma once

#include "../GameObject.h"
#include "../objects/Text.h"
#include "../objects/Button.h"
#include "../InterfaceObject.h"

class Death_screen : public InterfaceObject {
public:
	Death_screen();

	void update() override;
	void draw() override;

	Text playerScore_text;
	Text coinCount_text;
	GameObject panel_image;
	GameObject gameOver_image;
	Button respawn_button;
	Button house_button;
};