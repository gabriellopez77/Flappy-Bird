#pragma once

#include "../GameObject.h"

#include <vector>

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
};