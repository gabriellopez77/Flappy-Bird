#pragma once

#include "../InterfaceObject.h"

class Pause : public InterfaceObject {
public:
	Pause();

	void update() override;
	void draw() override;
};