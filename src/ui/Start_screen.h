#pragma once

#include "../GameObject.h"
#include "../objects/Button.h"

class Start_screen {
public:
	Start_screen();

	void update();
	void draw();

	GameObject* gameTitle_image;
	Button* start_button;
};