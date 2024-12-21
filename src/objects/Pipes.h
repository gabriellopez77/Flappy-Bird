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

	float veloY = 130.f;
	bool coinVisible = true;
	bool coinCollected = false;
	bool orange;
	bool signal = false;
};