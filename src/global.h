#pragma once

#include "../Dependencies/glm/glm.hpp"

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 650

#define PIPE_WIDTH 90
#define PIPE_HEIGHT 462
#define PIPE_MIN_HEIGHT 200
#define PIPE_MAX_HEIGHT 450

#define PLAYER_SIZE 60
#define PLAYER_START_POSITION glm::vec2(50, 300)

#define BACKGROUND_SPEED 0.8f
#define WORLD_SPEED 2.7f
#define GEN_PIPES_DELAY 2


#include "../Dependencies/glfw/glfw3.h"

#include "objects/Pipes.h"

#include <vector>

namespace gb {
	extern float deltaTime;
	extern float lastFrame;

	extern int windowX;
	extern int windowY;

	extern double mousePosX;
	extern double mousePosY;

	extern bool clicked;
	extern int action;
	extern bool paused;

	extern GLFWwindow* window;

	extern std::vector<Pipes*> pipes;
}