#pragma once

enum class ui {
	Hud,
	Start_screen,
	DressingRoom_screen,
	Death_screen,
};

class InterfaceObject {
public:
	virtual void update() = 0;
	virtual void draw() = 0;

	int id;
};