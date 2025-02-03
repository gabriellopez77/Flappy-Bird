#pragma once

#include "../../Dependencies/ml/Sprite.h"
#include "../InterfaceObject.h"
#include "../objects/Button.h"

class Start_screen : public InterfaceObject {
public:
	Start_screen();

	void update() override;
	void draw() override;

	ml::Sprite getReady_image;
	ml::Sprite clickToStart_image;
};