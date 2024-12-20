#pragma once

enum class ui : int {
	Empty,
	Main_screen,
	Hud_screen,
	Start_screen,
	DressingRoom_screen,
	Death_screen,
	Pause_screen
};

class InterfaceObject {
public:
	virtual void update() = 0;
	virtual void draw() = 0;

	int id;
};