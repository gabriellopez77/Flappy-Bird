#pragma once

#include "../GameObject.h"

class Scenery {
public:
	Scenery();
	void update();

	void drawBackground();
	void drawGround();

	GameObject* background1;
	GameObject* background2;
	GameObject* ground1;
	GameObject* ground2;
};