#pragma once

#include "../InterfaceObject.h"
#include "../objects/Button.h"

class Pause : public InterfaceObject {
public:
	Pause();

	Button unpause_button;

	void update() override;
	void draw() override;
};