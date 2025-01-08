#pragma once

#include "../GameObject.h"
#include "../InterfaceObject.h"
#include "../objects/Button.h"

class Main_screen : public InterfaceObject {
public:
	Main_screen();

	void update() override;
	void draw() override;
	void start() override;

	GameObject gameTitle_image;
	GameObject versionName_image;
	GameObject versionNumber_image;
	Button brush_button;
	Button start_button;
	Button exit_button;
};