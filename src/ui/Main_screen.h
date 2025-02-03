#pragma once

#include "../../Dependencies/ml/Sprite.h"
#include "../InterfaceObject.h"
#include "../objects/Button.h"

class Main_screen : public InterfaceObject {
public:
	Main_screen();

	void update() override;
	void draw() override;
	void start() override;

	ml::Sprite gameTitle_image;
	ml::Sprite versionName_image;
	ml::Sprite versionNumber_image;
	Button brush_button;
	Button start_button;
	Button exit_button;
};