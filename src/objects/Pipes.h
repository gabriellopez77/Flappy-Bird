#pragma once

#include "../GameObject.h"

class Pipes {
public:
	Pipes();

	void draw();
	void update();
	static void updatePipes();
	static void drawPipes();

	GameObject pipeTop;
	GameObject coin;
	GameObject pipeBottom;

	bool coinVisible = true;
};