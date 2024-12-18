#pragma once

#include "../GameObject.h"
#include "../objects/Text.h"
#include "../objects/Button.h"

class Death_screen {
public:
	Death_screen();

	void update();
	void draw();

	Text* playerScore_text;
	Text* coinCount_text;
	GameObject* board_image;
	GameObject* gameOver_image;
	Button* respawn_button;
	Button* house_button;
};