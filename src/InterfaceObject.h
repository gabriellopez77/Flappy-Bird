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
	// atualiza toda a interface
	virtual void update() = 0;

	// desenha toda a interface
	virtual void draw() = 0;

	// so é chamada uma vez ao mudar de interface
	virtual void start() {};

	// id da interface
	ui id;
};