#pragma once

#include "../GameObject.h"

#include "../InterfaceObject.h"
#include "../objects/Button.h"
#include "../objects/Text.h"

class DressingRoom : public InterfaceObject {
public:
	DressingRoom();

	void update() override;
	void draw() override;

	GameObject panel_image;
	Button close_button;
	//Text coinCount_text;
	//Text itemPrice1_text;
	//Text itemPrice2_text;
	//Text itemPrice3_text;
};