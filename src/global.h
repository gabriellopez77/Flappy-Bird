#pragma once

#define GAME_WIDTH 450
#define GAME_HEIGHT 650

#define PIPE_WIDTH 90
#define PIPE_HEIGHT 462

#include "objects/Pipes.h"

#include <vector>

namespace gb {
	extern float deltaTime;
	extern float lastFrame;

	extern int windowX;
	extern int windowY;

	extern std::vector<Pipes*> pipes;
}