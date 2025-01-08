#pragma once

#include "../GameObject.h"

class Pipes {
public:
	Pipes();
	static void updatePipes();
	static void drawPipes();

	GameObject pipeTop;
	GameObject coin;
	GameObject pipeBottom;
	GameObject scoreWall;

	float veloY = 130.f;
	bool coinVisible = true;
	bool coinCollected = false;
	bool orange;
	bool signal = false;
	bool passed = false;

private:
	void draw();
	void update();
};