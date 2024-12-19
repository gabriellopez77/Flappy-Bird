#pragma once

#include "../GameObject.h"

#include "../objects/Button.h"
#include "../objects/Text.h"

class DressingRoom {
public:
	DressingRoom();

	void update();
	void draw();

	GameObject* panel_image;
	Button* close_button;
	Text* coinCount_text;
	Text* itemPrice1_text;
	Text* itemPrice2_text;
	Text* itemPrice3_text;
};