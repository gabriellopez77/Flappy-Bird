#pragma once

#include "../GameObject.h"
#include "../InterfaceObject.h"
#include "../objects/Button.h"

class Start_screen : public InterfaceObject {
public:
	Start_screen();

	void update() override;
	void draw() override;

	GameObject getReady_image;
	GameObject clickToStart_image;
};