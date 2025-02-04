#pragma once

#include "../GameObject.h"

#include <array>

class Pipes {
public:
	Pipes();

	static void updatePipes();
	static void drawPipes();
	static void resetPipes();

	GameObject pipeTop;
	GameObject coin;
	GameObject pipeBottom;
	GameObject scoreWall;

	float forceY = 130.f;
	bool coinVisible = true;
	bool coinCollected = false;
	bool passed = false;
	bool orange;

	static Pipes pipes[3];

private:
	void reset();
	void draw();
	void update();
};